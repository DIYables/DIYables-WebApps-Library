<?php
/**
 * Conservative HTML Minifier for DIYables WebApps
 * 
 * This script safely minifies HTML files from html_dev/ folder and saves them to html/ folder
 * while preserving JavaScript functionality.
 * 
 * Usage: php scripts/minify.php
 */

// Define directories
$sourceDir = __DIR__ . '/../src/html_dev/';
$targetDir = __DIR__ . '/../src/html/';

// Ensure target directory exists
if (!is_dir($targetDir)) {
    mkdir($targetDir, 0755, true);
    echo "Created target directory: $targetDir\n";
}

/**
 * Function to generate short variable names dynamically, avoiding conflicts
 */
function generateShortName($avoidList = array()) {
    global $SHORT_NAME_COUNTER;
    
    while (true) {
        $candidate = '';
        
        // First 26: a-z
        if ($SHORT_NAME_COUNTER < 26) {
            $candidate = chr(ord('a') + $SHORT_NAME_COUNTER);
        }
        // Next 26: A-Z
        elseif ($SHORT_NAME_COUNTER < 52) {
            $candidate = chr(ord('A') + ($SHORT_NAME_COUNTER - 26));
        }
        // After 52: character + number combinations (a0, a1, a2, ..., z9, then A0, A1, ..., Z9)
        else {
            $adjustedIndex = $SHORT_NAME_COUNTER - 52;
            $charIndex = intval($adjustedIndex / 10); // Which character (a-z, then A-Z)
            $numIndex = $adjustedIndex % 10; // Which number (0-9)
            
            if ($charIndex < 26) {
                // Use lowercase a-z
                $firstChar = chr(ord('a') + $charIndex);
            } else {
                // Use uppercase A-Z
                $firstChar = chr(ord('A') + ($charIndex - 26));
            }
            
            $candidate = $firstChar . $numIndex;
        }
        
        // If this candidate is not in the avoid list, use it
        if (!in_array($candidate, $avoidList)) {
            $SHORT_NAME_COUNTER++; // Increment for next call
            return $candidate;
        }
        
        // Otherwise, try the next index
        $SHORT_NAME_COUNTER++;
    }
}


function removeBetween($content, $start, $end) {
    while (strpos($content, $start) !== false && strpos($content, $end) !== false) {
        $start_pos = strpos($content, $start);
        $end_pos = strpos($content, $end, $start_pos);
        if ($end_pos !== false) {
            $content = substr($content, 0, $start_pos) . substr($content, $end_pos + strlen($end));
        } else {
            break;
        }
    }
    return $content;
}

function removeLoop($find, $replace, $content) {
    while (strpos($content, $find) !== false) {
        $content = str_replace($find, $replace, $content);
    }
    return $content;
}
function removeSpaceAround($around, $content) {
    $content = removeLoop(" $around", $around, $content);
    $content = removeLoop("$around ", $around, $content);
    return $content;
}

function getBetween($content, $start, $end, $included_tag = true) {
    $block = "";
    $start_pos = strpos($content, $start);
	if ($start_pos !== false) {
        $end_pos = strpos($content, $end, $start_pos);
        if ($end_pos !== false) {
			if($included_tag)
				$block = substr($content, $start_pos, $end_pos + strlen($end));
			else
				$block = substr($content, $start_pos + strlen($start), $end_pos);
        } else {
            
        }
    }
    return $block;
}

/**
 * Remove HTML comments while preserving conditional comments
 */
function removeHtmlComments($content) {
	return removeBetween($content, '<!--', '-->');
}

/**
 * Clean up whitespace and indentation
 */
function cleanWhitespace($content) {
    // Remove carriage returns from entire content
    $content = str_replace("\r", '', $content);
    
    // Remove spaces after newlines (indentation removal)
    $lines = explode("\n", $content);
    foreach ($lines as $i => $line) {
        $lines[$i] = ltrim($line);
    }
    $content = implode("\n", $lines);
    
    // Remove extra whitespace between tags
    $content = str_replace('> <', '><', $content);
    $content = str_replace('>  <', '><', $content);
    $content = str_replace('>   <', '><', $content);
    $content = str_replace('>    <', '><', $content);
    
    // Remove newlines after closing tags
    $content = str_replace(">\n", ">", $content);
    
    return $content;
}

/**
 * Remove CSS comments using pure string operations
 */
function removeCssComments($css) {
	return removeBetween($css, '/*', '*/');
}

/**
 * Find CSS class names in CSS content
 */
function findCssClasses($css) {
    $cssClasses = array();
    $cssLines = explode("\n", $css);
    foreach ($cssLines as $line) {
        $line = trim($line);
        if (strpos($line, '.') !== false) {
            // Find class selectors
            $dotPos = strpos($line, '.');
            while ($dotPos !== false) {
                $remaining = substr($line, $dotPos + 1);
                $className = '';
                for ($i = 0; $i < strlen($remaining); $i++) {
                    $char = $remaining[$i];
                    if (ctype_alnum($char) || $char === '_' || $char === '-') {
                        $className .= $char;
                    } else {
                        break;
                    }
                }
                if (!empty($className) && ctype_alpha($className[0])) {
                    $cssClasses[] = $className;
					echo "CLASSNAME: $className\n";
                }
                $dotPos = strpos($line, '.', $dotPos + 1);
            }
        }
    }

    return array_unique($cssClasses);
}

/**
 * Find CSS class names in HTML content
 */
function findHtmlClasses($content) {
    $htmlClasses = array();
    $pos = 0;
    while (($pos = strpos($content, 'class=', $pos)) !== false) {
        $pos += 6; // Move past 'class='
        
        // Skip any whitespace
        while ($pos < strlen($content) && ($content[$pos] === ' ' || $content[$pos] === '\t')) {
            $pos++;
        }
        
        if ($pos >= strlen($content)) break;
        
        // Get the quote character (either " or ')
        $quote = $content[$pos];
        if ($quote !== '"' && $quote !== "'") continue;
        
        $pos++; // Move past opening quote
        $start = $pos;
        
        // Find the closing quote
        while ($pos < strlen($content) && $content[$pos] !== $quote) {
            $pos++;
        }
        
        if ($pos < strlen($content)) {
            // Extract the class list between quotes
            $classList = substr($content, $start, $pos - $start);
            
            // Split by whitespace to get individual classes
            $classes = explode(' ', trim($classList));
            foreach ($classes as $class) {
                $class = trim($class);
                if (!empty($class)) {
                    $htmlClasses[] = $class;
                }
            }
        }
        
        $pos++; // Move past closing quote
    }
    return $htmlClasses;
}

function minifyCss($css, $cssClassMap) {
	// Replace CSS class definitions
	foreach ($cssClassMap as $originalClass => $shortClass) {
		$css = str_replace('.' . $originalClass . '{', '.' . $shortClass . '{', $css);
		$css = str_replace('.' . $originalClass . ',', '.' . $shortClass . ',', $css);
		$css = str_replace('.' . $originalClass . ' ', '.' . $shortClass . ' ', $css);
		$css = str_replace('.' . $originalClass . ':', '.' . $shortClass . ':', $css);
		$css = str_replace('.' . $originalClass . '.', '.' . $shortClass . '.', $css);
	}
	
	return $css;
}
/**
 * Apply CSS minification
 */
function cleanCssContent($css) {
	// Remove CSS comments
    $css = removeCssComments($css);

    // Process line by line to trim each line
    $lines = explode("\n", $css);
    $trimmedLines = array();
    
    foreach ($lines as $line) {
        $line = trim($line);
        if (!empty($line)) {
            $trimmedLines[] = $line;
        }
    }
    
    // Join lines back and continue with minification
    $css = implode("\n", $trimmedLines);
    
    // Remove extra whitespace
    $css = removeLoop('  ', ' ', $css);
    
    // Remove spaces around CSS punctuation
    $css = removeSpaceAround('{', $css);
    $css = removeSpaceAround('}', $css);
    $css = removeSpaceAround(':', $css);
    $css = removeSpaceAround(';', $css);
    $css = removeSpaceAround(',', $css);
    $css = removeSpaceAround('>', $css);
    $css = removeSpaceAround('+', $css);
    $css = removeSpaceAround('~', $css);
    
    // Remove trailing semicolons before }
    $css = removeLoop(';}', '}', $css);
    
    // Remove leading/trailing whitespace
    $css = trim($css);
    
    return $css;
}

/**
 * Remove JavaScript comments and clean up code
 */
function cleanJavaScript($js) {
	// remove block comment
	$js = removeBetween($js, '/*', '*/');
    
    // Process line by line
    $lines = explode("\n", $js);
    $minifiedLines = array();
    
    foreach ($lines as $line) {
		 // Remove leading/trailing spaces
        $line = trim($line);
        // Remove tabs
        $line = str_replace("\t", ' ', $line);
		$line = removeLoop('  ', ' ', $line);
        
        // Remove full line comments (lines that start with //)
        if (strpos(trim($line), '//') === 0) {
            continue; // Skip this line entirely
        }
        
        // Only add non-empty lines
        if (!empty($line)) {
            // Remove embedded line comments with spaces around //
            $commentPos = strpos($line, ' //');
            if ($commentPos !== false) {
                $line = trim(substr($line, 0, $commentPos));
            }
            
            // Trim the line one more time
            $line = trim($line);
            
            // Add line if still not empty after comment removal and trim
            if (!empty($line)) {
                $minifiedLines[] = $line;
            }
        }
    }
    
    $result = implode("\n", $minifiedLines);
    // Safe specific keyword optimizations
    $result = removeSpaceAround('(', $result);
    $result = removeSpaceAround('{', $result);
    $result = removeSpaceAround('}', $result);
    $result = removeSpaceAround('=', $result);
    $result = removeSpaceAround('+', $result);
    $result = removeSpaceAround('-', $result);
    $result = removeSpaceAround('*', $result);
    $result = removeSpaceAround('/', $result);
    $result = removeSpaceAround('!', $result);
    $result = removeSpaceAround('?', $result);
    $result = removeSpaceAround(':', $result);
    $result = removeSpaceAround(';', $result);
    $result = removeSpaceAround(',', $result);
    $result = removeSpaceAround('>', $result);
    $result = removeSpaceAround('<', $result);
    $result = removeSpaceAround('~', $result);
    $result = removeSpaceAround('&', $result);
    $result = removeSpaceAround('|', $result);
    $result = removeSpaceAround('%', $result);
    
    return $result;
}

/**
 * Get JavaScript reserved words that should not be minified
 */
function getJavaScriptReservedWords() {
    return array(
        'function', 'var', 'let', 'const', 'if', 'else', 'for', 'while', 'do', 'switch', 'case', 'default',
        'break', 'continue', 'return', 'try', 'catch', 'finally', 'throw', 'new', 'delete', 'typeof', 'instanceof',
        'in', 'of', 'class', 'extends', 'super', 'static', 'import', 'export', 'from', 'as', 'async', 'await',
        'true', 'false', 'null', 'undefined', 'this', 'arguments', 'prototype', 'constructor',
        'Object', 'Array', 'String', 'Number', 'Boolean', 'Date', 'Math', 'JSON', 'console', 'window', 'document'
    );
}

/**
 * Find all function names in JavaScript code
 */
function findJavaScriptFunctions($js) {
    $allFunctions = array();
    $lines = explode("\n", $js);
    foreach ($lines as $line) {
        $trimmedLine = trim($line);
        if (strpos($trimmedLine, 'function ') === 0) {
            // Extract function name
            $functionPart = explode('function ', $trimmedLine, 2)[1];
            $functionPart = explode('(', $functionPart, 2)[0];
            $allFunctions[] = $functionPart;
			echo "FUNCTIONPART: $functionPart\n";
        }
    }
    return array_unique($allFunctions);
}

/**
 * Extract variable name from a string, stopping at delimiter characters
 */
function extractVariableName($varPart) {
    $varName = '';
    $endChars = array('=', ';', ')', '}', ' ', ':', '[', '(');
    foreach ($endChars as $endChar) {
        if (strpos($varPart, $endChar) !== false) {
            $varName = trim(explode($endChar, $varPart)[0]);
            break;
        }
    }
    if (empty($varName)) {
        $varName = $varPart;
    }
    
    // Clean up variable name - only keep valid identifier characters
    $cleanVarName = '';
    for ($i = 0; $i < strlen($varName); $i++) {
        $char = $varName[$i];
        if (ctype_alnum($char) || $char === '_' || $char === '$') {
            $cleanVarName .= $char;
        } else {
            break;
        }
    }
    
    return $cleanVarName;
}

/**
 * Find variable declarations in JavaScript code
 */
function findVariableDeclarations($trimmedLine) {
    $variables = array();
    
    foreach (array('var ', 'let ', 'const ') as $keyword) {
        $keywordPos = strpos($trimmedLine, $keyword);
        if ($keywordPos !== false) {
            // Check if it's at word boundary
            if ($keywordPos === 0 || !ctype_alnum($trimmedLine[$keywordPos - 1])) {
                $afterKeyword = trim(substr($trimmedLine, $keywordPos + strlen($keyword)));
                
                // Handle multiple variables separated by commas OR semicolons
                $variableParts = explode(',', $afterKeyword);
                foreach ($variableParts as $varPart) {
                    $varPart = trim($varPart);
                    
                    // Also check for semicolon-separated variables in minified code
                    $semicolonParts = explode(';', $varPart);
                    foreach ($semicolonParts as $semiPart) {
                        $semiPart = trim($semiPart);
                        if (empty($semiPart)) continue;
                        
                        // Look for another variable declaration keyword in this part
                        foreach (array('let ', 'const ', 'var ') as $innerKeyword) {
                            if (strpos($semiPart, $innerKeyword) !== false) {
                                $innerPos = strpos($semiPart, $innerKeyword);
                                if ($innerPos !== false) {
                                    $semiPart = trim(substr($semiPart, $innerPos + strlen($innerKeyword)));
                                }
                                break;
                            }
                        }
                        
                        $cleanVarName = extractVariableName($semiPart);
                        if (!empty($cleanVarName) && (ctype_alpha($cleanVarName[0]) || $cleanVarName[0] === '_' || $cleanVarName[0] === '$')) {
                            $variables[] = $cleanVarName;
                        }
                    }
                }
                break; // Found the keyword, no need to check others
            }
        }
    }
    
    return $variables;
}

/**
 * Find function parameters in JavaScript code
 */
function findFunctionParameters($trimmedLine) {
    $variables = array();
    
    if (strpos($trimmedLine, 'function ') !== false && strpos($trimmedLine, '(') !== false) {
        $functionPos = strpos($trimmedLine, 'function ');
        // Make sure it's at word boundary
        if ($functionPos === 0 || !ctype_alnum($trimmedLine[$functionPos - 1])) {
            $openParen = strpos($trimmedLine, '(', $functionPos);
            $closeParen = strpos($trimmedLine, ')', $openParen);
            if ($openParen !== false && $closeParen !== false) {
                $paramString = trim(substr($trimmedLine, $openParen + 1, $closeParen - $openParen - 1));
                if (!empty($paramString)) {
                    $params = explode(',', $paramString);
                    foreach ($params as $param) {
                        $cleanParam = extractVariableName(trim($param));
                        if (!empty($cleanParam) && (ctype_alpha($cleanParam[0]) || $cleanParam[0] === '_' || $cleanParam[0] === '$')) {
                            $variables[] = $cleanParam;
                        }
                    }
                }
            }
        }
    }
    
    return $variables;
}

/**
 * Find for loop variables in JavaScript code
 */
function findForLoopVariables($trimmedLine) {
    $variables = array();
    
    if (strpos($trimmedLine, 'for') !== false && strpos($trimmedLine, '(') !== false) {
        $forPos = strpos($trimmedLine, 'for');
        // Make sure it's at word boundary
        if ($forPos === 0 || !ctype_alnum($trimmedLine[$forPos - 1])) {
            $openParen = strpos($trimmedLine, '(', $forPos);
            if ($openParen !== false) {
                $remaining = substr($trimmedLine, $openParen + 1);
                $parts = explode(';', $remaining, 2);
                if (count($parts) >= 1) {
                    $initPart = trim($parts[0]);
                    foreach (array('var ', 'let ', 'const ') as $keyword) {
                        if (strpos($initPart, $keyword) !== false) {
                            $afterKeyword = trim(substr($initPart, strpos($initPart, $keyword) + strlen($keyword)));
                            $cleanVarName = extractVariableName($afterKeyword);
                            if (!empty($cleanVarName) && (ctype_alpha($cleanVarName[0]) || $cleanVarName[0] === '_' || $cleanVarName[0] === '$')) {
                                $variables[] = $cleanVarName;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    
    return $variables;
}

/**
 * Find catch variables in JavaScript code
 */
function findCatchVariables($trimmedLine) {
    $variables = array();
    
    if (strpos($trimmedLine, 'catch') !== false && strpos($trimmedLine, '(') !== false) {
        $catchPos = strpos($trimmedLine, 'catch');
        // Make sure it's at word boundary
        if ($catchPos === 0 || !ctype_alnum($trimmedLine[$catchPos - 1])) {
            $openParen = strpos($trimmedLine, '(', $catchPos);
            $closeParen = strpos($trimmedLine, ')', $openParen);
            if ($openParen !== false && $closeParen !== false) {
                $catchVar = trim(substr($trimmedLine, $openParen + 1, $closeParen - $openParen - 1));
                $cleanCatchVar = extractVariableName($catchVar);
                if (!empty($cleanCatchVar) && (ctype_alpha($cleanCatchVar[0]) || $cleanCatchVar[0] === '_' || $cleanCatchVar[0] === '$')) {
                    $variables[] = $cleanCatchVar;
                }
            }
        }
    }
    
    return $variables;
}

/**
 * Find all variables in JavaScript code
 */
function findJavaScriptVariables($js) {
    $allVariables = array();
    $reservedWords = getJavaScriptReservedWords();
    
    $lines = explode("\n", $js);
    foreach ($lines as $line) {
        $trimmedLine = trim($line);
        
        // Find variable declarations
        $variables = findVariableDeclarations($trimmedLine);
        $allVariables = array_merge($allVariables, $variables);
        
        // Find function parameters
        $variables = findFunctionParameters($trimmedLine);
        $allVariables = array_merge($allVariables, $variables);
        
        // Find for loop variables
        $variables = findForLoopVariables($trimmedLine);
        $allVariables = array_merge($allVariables, $variables);
        
        // Find catch variables
        $variables = findCatchVariables($trimmedLine);
        $allVariables = array_merge($allVariables, $variables);
    }
    
    // Filter out reserved words and process variables
    $allVariables = array_unique($allVariables);
    $variablesToMap = array();
    $singleCharVariables = array();
    
    foreach ($allVariables as $variableName) {
        // Skip JavaScript reserved words
        if (in_array($variableName, $reservedWords)) {
            echo "AVOID: " . $variableName . " (reserved word)\n";
            continue;
        }
        
        // If it's a single character variable, add to avoid list but don't map
        if (strlen($variableName) == 1) {
            if (!in_array($variableName, $singleCharVariables)) {
                $singleCharVariables[] = $variableName;
                echo "AVOID: " . $variableName . " (single-character variable)\n";
            }
        } else {
            // Multi-character variables are candidates for mapping
            if (!in_array($variableName, $variablesToMap)) {
                $variablesToMap[] = $variableName;
            }
        }
    }
    
    return array($variablesToMap, $singleCharVariables);
}

/**
 * Apply function name replacements in JavaScript
 */
function applyFunctionReplacements($js, $functionMap) {
    $sortedFunctions = array_keys($functionMap);
    usort($sortedFunctions, function($a, $b) { return strlen($b) - strlen($a); });
    
    foreach ($sortedFunctions as $originalName) {
        $shortName = $functionMap[$originalName];
        // Replace function declaration
        $js = str_replace("function $originalName(", "function $shortName(", $js);
        // Replace function calls (with word boundaries to avoid partial matches)
        $js = preg_replace('/\b' . preg_quote($originalName) . '\b(?=\s*\()/', $shortName, $js);
        // Replace function references in addEventListener and other callback contexts
        $js = preg_replace('/\b' . preg_quote($originalName) . '\b(?!\s*\()/', $shortName, $js);
    }
    
    return $js;
}

/**
 * Apply variable name replacements in JavaScript
 */
function applyVariableReplacements($js, $variableMap) {
    $sortedVariables = array_keys($variableMap);
    usort($sortedVariables, function($a, $b) { return strlen($b) - strlen($a); });
    
    foreach ($sortedVariables as $originalName) {
        $shortName = $variableMap[$originalName];
        
        // Variable declarations
        $js = str_replace("var $originalName", "var $shortName", $js);
        $js = str_replace("let $originalName", "let $shortName", $js);
        $js = str_replace("const $originalName", "const $shortName", $js);
        
        // Define prefix and suffix combinations for bulk replacement
        $prefixes = array(';', '=', '(', ')', '/', '!', ',', '+', '-', '*', '{', "[", "}", "]", '<', '>', "&", "|", ":", "?", '%', "...", " ");
        $suffixes = array(';', '=', '(', ')', '/', '!', ',', '+', '-', '*', '{', "[", "}", "]", '<', '>', "&", "|", ":", "?", '%', ".");
        
        // Apply all prefix-suffix combinations
        foreach ($prefixes as $prefix) {
            foreach ($suffixes as $suffix) {
                if($prefix === '{' && $suffix === ':') {
                    continue;
                }
                
                if($prefix === ',' && $suffix === ':') {
                    continue;
                }

                $js = str_replace("$prefix$originalName$suffix", "$prefix$shortName$suffix", $js);
            }
        }
        
        // Special cases that don't fit the pattern
        $js = str_replace("($originalName)", "($shortName)", $js);
    }
    
    return $js;
}

/**
 * Apply CSS class replacements in HTML content
 */
function applyCssClassReplacements($content, $cssClassMap) {
	$tags = array(
		" class=",              // class attributes in HTML
		".className=",          // get/set full class string in JS
		".classList.add(",      // add a specific class in JS
		".classList.remove(",   // remove a specific class in JS
		".classList.toggle(",   // toggle a specific class in JS
		".classList.contains(", // check if a specific class exists
		".classList.replace(",  // replace a specific class with another
		".getAttribute(\"class\")", // get full class string
		".setAttribute(\"class\"",   // set full class string
		".querySelector(",      // select by CSS class in JS
		".querySelectorAll(",   // select all matching elements in JS
		".getElementsByClassName(" // get elements by specific class
	);
	
	foreach($tags as $tag) {
		$quotes  = array("'", '"');
		foreach($quotes as $quote) {
			$tag_start = $tag . $quote;
			if(strpos($tag, "querySelector") !== false)
				$tag_start .= ".";
			$parts = explode($tag_start, $content);
			for($part_index = 1; $part_index < count($parts); $part_index++) {
				$part = $parts[$part_index];
				$part = explode($quote, $part, 2);
				
				$classes = $part[0];
				$classes = trim($classes);
				if($classes == "") {
					echo "ERROR\n";
					break;
				}
				echo "CLASSES: $classes\n";

				$classes = removeLoop('  ', ' ', $classes);
				$classes = explode(" ", $classes);
				$new_classes = array();
				foreach($classes as $class) {
					if(array_key_exists($class, $cssClassMap))
						$new_classes[] = $cssClassMap[$class];
					else
						$new_classes[] = $class;
				}
				
				$part[0] = implode(" ", $new_classes);
				
				$parts[$part_index] = implode($quote, $part);;
			}

			$content = implode($tag_start, $parts);
			
		}
	}
    
    
    return $content;
}

/**
 * Apply function replacements in HTML attributes
 */
function applyFunctionReplacementsInHtml($content, $functionMap) {
    $sortedFunctions = array_keys($functionMap);
    usort($sortedFunctions, function($a, $b) { return strlen($b) - strlen($a); });
	
	$events = array("onclick", "ondblclick", "onmousedown", "onmouseup", "onmousemove", "onmouseover", "onmouseout", "onmouseenter", "onmouseleave", "oncontextmenu", "oninput", "onchange", "onfocus", "onblur", "onsubmit", "onreset", "onselect", "oninvalid", "ontouchstart", "ontouchend", "ontouchmove", "ontouchcancel", "onpointerdown", "onpointerup", "onpointermove", "onpointerover", "onpointerout", "onpointerenter", "onpointerleave", "ongotpointercapture", "onlostpointercapture", "onpointercancel", "onload", "onbeforeunload", "onunload", "onresize", "onscroll", "onerror", "onhashchange", "onpopstate", "onstorage", "ononline", "onoffline", "onwheel", "onscrollend", "onabort", "onshow", "ontoggle");
    
    foreach ($sortedFunctions as $originalName) {
		$shortName = $functionMap[$originalName];
		foreach ($events as $event) {
			$content = str_replace("$event='$originalName(", "$event='$shortName(", $content);
			$content = str_replace("$event=\"$originalName(", "$event=\"$shortName(", $content);
		}
    }
    
    return $content;
}

/**
 * Safely minify HTML content while preserving functionality
 */
function minifyHtml($content, $sourceFile = '') {
	$cssClasses = array();
    // Check if this is a home page file that should be excluded from CSS class name shortening
    $isHomePageFile = (strpos($sourceFile, 'home_page') !== false);
    
    // Step 1: Remove HTML comments and clean whitespace
    $content = removeHtmlComments($content);
    $content = cleanWhitespace($content);
    
    // Step 2: Minify CSS within <style> tags
    $cssClassMap = array(); // Track CSS class name mappings
	
	$css_origin = getBetween($content, "<style>", "</style>", false);
    $css_minified = cleanCssContent($css_origin);
	    
	// Skip CSS class name shortening for home page files
	if (!$isHomePageFile) {
		// Find all CSS class definitions and create mappings
		$cssClasses = findCssClasses($css_minified);

		foreach ($cssClasses as $className) {
			if (!isset($cssClassMap[$className])) {
				$shortName = generateShortName(array_values($cssClassMap));
				$cssClassMap[$className] = $shortName;
				echo $shortName . " <= ." . $className . " (CSS class)\n";
			}
		}

		$css_minified = minifyCss($css_minified, $cssClassMap);
	}
	$content = str_replace($css_origin, $css_minified, $content);
	
    
    // Step 3: Minify JavaScript within <script> tags
    $functionMap = array(); // Track function name mappings
    $variableMap = array(); // Track variable name mappings
	
	$js_origin = getBetween($content, "<script>", "</script>", false);
	 // Clean JavaScript
   $js_minified = cleanJavaScript($js_origin);
    // Find all function names
    $allFunctions = findJavaScriptFunctions($js_minified);

    // Find all variables
    list($variablesToMap, $singleCharVariables) = findJavaScriptVariables( $js_minified);
        
        // Create function mappings
        foreach ($allFunctions as $functionName) {
            if (!isset($functionMap[$functionName])) {
                $shortName = generateShortName($singleCharVariables);
                $functionMap[$functionName] = $shortName;
                echo $shortName . " <= " . $functionName . " (function)\n";
            }
        }
        
        // Create variable mappings
        foreach ($variablesToMap as $variableName) {
            if (!isset($variableMap[$variableName])) {
                $shortName = generateShortName($singleCharVariables);
                $variableMap[$variableName] = $shortName;
                echo $shortName . " <= " . $variableName . " (variable)\n";
            }
        }

        
		 $js_minified = str_replace(";\n", ";", $js_minified);
		 $js_minified = str_replace("}\n", "}", $js_minified);
		 $js_minified = str_replace("{\n", "{", $js_minified);
		 $js_minified = str_replace(")\n", ")", $js_minified);
		 $js_minified = str_replace(">\n", ">", $js_minified);
		 $js_minified = str_replace("=\n", "=", $js_minified);
		 $js_minified = str_replace("+\n", "+", $js_minified);
		 $js_minified = str_replace("\n}", "}", $js_minified);
		 $js_minified = str_replace(",\n", ",", $js_minified);
		 $js_minified = str_replace("else\n", "else ", $js_minified);
		
		// Apply function name replacements
        $js_minified = applyFunctionReplacements($js_minified, $functionMap);
		$js_minified = applyVariableReplacements($js_minified, $variableMap);
	

	$content = str_replace($js_origin, $js_minified, $content);
    
    // Step 4: Apply CSS class replacements in HTML content (skip for home page files)
    if (!empty($cssClassMap) && !$isHomePageFile) {
        $content = applyCssClassReplacements($content, $cssClassMap);
    }
    
    // Step 5: Apply function replacements in HTML attributes
    if (!empty($functionMap)) {
        $content = applyFunctionReplacementsInHtml($content, $functionMap);
    }
    
    // Step 6: Final cleanup
    $lines = explode("\n", $content);
    $trimmedLines = array();
    
    foreach ($lines as $line) {
        $line = trim($line);
        if (!empty($line)) {
            $trimmedLines[] = $line;
        }
    }
    
    $content = implode("", $trimmedLines);
    
    return trim($content);
}

/**
 * Process a single file
 */
function processFile($sourceFile, $targetFile) {
    echo "Processing: " . basename($sourceFile) . "\n";
    
    $content = file_get_contents($sourceFile);
    if ($content === false) {
        echo "  ERROR: Could not read source file\n";
        return false;
    }
    
    $originalSize = strlen($content);
    
    // Extract the HTML content from the C++ header file - Pure string approach
    $progmemPos = strpos($content, 'PROGMEM = R"');
    if ($progmemPos !== false) {
        // Find the delimiter
        $delimiterStart = $progmemPos + 12; // After 'PROGMEM = R"'
        $openParenPos = strpos($content, '(', $delimiterStart);
        if ($openParenPos !== false) {
            $delimiter = substr($content, $delimiterStart, $openParenPos - $delimiterStart);
            
            // Find the HTML content between the delimiters
            $htmlStart = $openParenPos + 1;
            $closingPattern = ')' . $delimiter . '";';
            $htmlEnd = strpos($content, $closingPattern, $htmlStart);
            
            if ($htmlEnd !== false) {
                $htmlContent = substr($content, $htmlStart, $htmlEnd - $htmlStart);
                
                // Minify the HTML content
                $minifiedHtml = minifyHtml($htmlContent, $sourceFile);
				//file_put_contents($targetFile, $minifiedHtml); return;
                
                // Replace the original HTML with minified version
                $minifiedContent = str_replace(
                    'R"' . $delimiter . '(' . $htmlContent . ')' . $delimiter . '"',
                    'R"' . $delimiter . '(' . $minifiedHtml . ')' . $delimiter . '"',
                    $content
                );
                
                $newSize = strlen($minifiedContent);
                $savings = $originalSize - $newSize;
                $percentage = round(($savings / $originalSize) * 100, 1);
                
                // Write minified content to target file
                if (file_put_contents($targetFile, $minifiedContent) !== false) {
                    echo "  SUCCESS: Saved " . $savings . " bytes ({$percentage}% reduction)\n";
                    echo "  Original: {$originalSize} bytes → Minified: {$newSize} bytes\n";
                    return true;
                } else {
                    echo "  ERROR: Could not write target file\n";
                    return false;
                }
            } else {
                echo "  WARNING: Could not find closing delimiter\n";
                copy($sourceFile, $targetFile);
                return true;
            }
        } else {
            echo "  WARNING: Could not find opening parenthesis\n";
            copy($sourceFile, $targetFile);
            return true;
        }
    } else {
        echo "  WARNING: No HTML content found in file\n";
        // Copy file as-is if no HTML content found
        copy($sourceFile, $targetFile);
        return true;
    }
}

$SHORT_NAME_COUNTER = 0;
// Main execution
echo "=== DIYables WebApps Conservative HTML Minifier ===\n";
echo "Source: $sourceDir\n";
echo "Target: $targetDir\n\n";

if (!is_dir($sourceDir)) {
    die("ERROR: Source directory does not exist: $sourceDir\n");
}

// Get all .h files from source directory
$files = glob($sourceDir . '*.h');

if (empty($files)) {
    die("ERROR: No .h files found in source directory\n");
}

$totalFiles = 0;
$successFiles = 0;
$totalOriginalSize = 0;
$totalMinifiedSize = 0;

//exit();

foreach ($files as $sourceFile) {
    $filename = basename($sourceFile);
    $targetFile = $targetDir . $filename;
    
    $totalFiles++;
    
    $originalSize = filesize($sourceFile);
    $totalOriginalSize += $originalSize;
    
    //if (strpos($targetFile, "table") === false) continue;
	$SHORT_NAME_COUNTER = 0;
    if (processFile($sourceFile, $targetFile)) {
        $successFiles++;
        $minifiedSize = filesize($targetFile);
        $totalMinifiedSize += $minifiedSize;
    }
    
    echo "\n";
}

// Summary
echo "=== MINIFICATION SUMMARY ===\n";
echo "Total files processed: $totalFiles\n";
echo "Successfully minified: $successFiles\n";

if ($totalOriginalSize > 0) {
    $totalSavings = $totalOriginalSize - $totalMinifiedSize;
    $totalPercentage = round(($totalSavings / $totalOriginalSize) * 100, 1);
    
    echo "Total original size: " . number_format($totalOriginalSize) . " bytes\n";
    echo "Total minified size: " . number_format($totalMinifiedSize) . " bytes\n";
    echo "Total savings: " . number_format($totalSavings) . " bytes ({$totalPercentage}% reduction)\n";
}

echo "\nMinification complete! JavaScript functionality preserved.\n";
?>
