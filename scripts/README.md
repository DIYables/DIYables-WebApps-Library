# HTML Minifier for DIYables WebApps

> **⚠️ NOTE FOR USERS:** This documentation is intended for developers who want to modify the source code of the DIYables WebApps library. If you are simply using the library in your Arduino projects, you can safely ignore this folder and its contents. **Additionally, this minifier may contain bugs and is not recommended for production use.**

## Overview

This folder contains scripts to minify HTML files for Arduino compilation during library development.

- **Development**: Edit files in `src/html_dev/` folder
- **Production**: Minified files are generated in `src/html/` folder
- **Compilation**: Arduino IDE uses files from `src/html/` folder

## Usage

### Method 1: Using PHP directly
```bash
cd scripts
php minify.php
```

### Method 2: Using PowerShell (Windows)
```powershell
cd scripts
php minify.php
```

### Method 3: Using Terminal (Linux/Mac)
```bash
cd scripts
php minify.php
```

## What the minifier does

1. **Removes whitespace**: Eliminates unnecessary spaces, tabs, and newlines in HTML/CSS
2. **Minifies CSS**: Aggressively compresses CSS within `<style>` tags
3. **Preserves JavaScript**: Safely minifies JavaScript while maintaining functionality
4. **Removes comments**: Eliminates HTML and CSS comments (JavaScript comments preserved when needed)
5. **Maintains structure**: Preserves essential code structure and functionality

## Workflow

1. Make changes to HTML files in `src/html_dev/`
2. Run the minifier script
3. Commit both `html_dev/` and `html/` folders to version control
4. Arduino compilation uses the minified files from `html/`

## File Size Reduction

Typical reductions with the safe minifier:
- **HTML/CSS**: 40-50% size reduction
- **JavaScript**: Conservative 15-25% reduction (functionality preserved)
- **Overall**: Usually 35-45% total file size reduction

## Requirements

- PHP 7.0 or higher
- Write permissions to `src/html/` folder

## Notes

- The minifier preserves the C++ header file structure
- Raw string literals are properly handled
- Minified files maintain the same filename as originals
- Always test functionality after minification
