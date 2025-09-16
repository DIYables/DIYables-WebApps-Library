#ifndef WEB_SLIDER_HTML_H
#define WEB_SLIDER_HTML_H

const char WEB_SLIDER_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Remote Slider - DIYables WebApp</title>
    <link rel="icon" href="https://diyables.io/images/page/diyables.svg">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            background: white;
            height: 100vh;
            margin: 0;
            padding: 0;
            display: flex;
            flex-direction: column;
            box-sizing: border-box;
        }
        
        .container {
            background: white;
            border-radius: 0;
            box-shadow: none;
            width: 100%;
            flex: 1;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px 40px;
            text-align: center;
            display: flex;
            flex-direction: column;
            justify-content: flex-start;
            box-sizing: border-box;
            overflow: hidden;
        }
        
        .header {
            margin-top: 10px;
            margin-bottom: 20px;
            position: relative;
        }
        
        .header h1 {
            font-size: 2.0em;
            margin-bottom: 5px;
        }
        
        .header h1 .emoji {
            background: none;
            -webkit-background-clip: initial;
            -webkit-text-fill-color: initial;
            color: initial;
        }
        
        .header h1 .text {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
        }
        
        .header p {
            color: #666;
            font-size: 1.0em;
        }
        
        .top-nav {
            padding: 10px 20px;
            border-bottom: 1px solid #e9ecef;
            margin: -40px -40px 0 -40px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .home-link {
            color: #667eea;
            text-decoration: none;
            font-size: 1.1em;
            font-weight: bold;
            transition: all 0.3s;
            padding: 8px 12px;
            border-radius: 6px;
            background: rgba(102, 126, 234, 0.1);
        }
        
        .home-link:hover {
            background: rgba(102, 126, 234, 0.2);
            transform: scale(1.05);
        }
        
        .tutorial-link {
            color: #007bff;
            text-decoration: none;
            font-size: 1.0em;
            font-weight: bold;
            transition: all 0.3s;
            padding: 8px 12px;
            border-radius: 6px;
            background: rgba(0, 123, 255, 0.1);
        }
        
        .tutorial-link:hover {
            background: rgba(0, 123, 255, 0.2);
            transform: scale(1.05);
        }
        
        .websocket-status {
            background: #f8f9fa;
            padding: 5px 20px;
            border-bottom: 1px solid #e9ecef;
            text-align: center;
            font-size: 0.9em;
            color: black;
        }
        
        .websocket-status #connectionText {
            font-weight: bold;
        }
        
        .footer {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            text-align: center;
            padding: 15px 20px;
            width: 100%;
            font-size: 0.9em;
            border-top: 1px solid rgba(255, 255, 255, 0.1);
            position: fixed;
            bottom: 0;
            left: 0;
            z-index: 1000;
            height: 40px;
            box-sizing: border-box;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        
        .footer a {
            color: white;
            text-decoration: none;
            font-weight: bold;
            transition: all 0.3s ease;
        }
        
        .footer a:hover {
            color: rgba(255, 255, 255, 0.8);
            text-decoration: underline;
        }
        
        .connection-status {
            padding: 8px 16px;
            border-radius: 20px;
            font-size: 0.9em;
            font-weight: bold;
        }
        
        .connection-status.connected {
            background: #d4edda;
            color: #155724;
            border: 1px solid #c3e6cb;
        }
        
        .connection-status.disconnected {
            background: #f8d7da;
            color: #721c24;
            border: 1px solid #f5c6cb;
        }
        
        .sliders-container {
            display: flex;
            flex-direction: column;
            gap: 40px;
            margin-bottom: 40px;
        }
        
        .slider-group {
            background: linear-gradient(135deg, #f093fb 0%, #f5576c 20%, #4facfe 40%, #00f2fe 60%, #43e97b 80%, #38f9d7 100%);
            border-radius: 20px;
            padding: 30px;
            color: white;
            position: relative;
            overflow: hidden;
        }
        
        .slider-group::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: rgba(255,255,255,0.1);
            backdrop-filter: blur(10px);
            border-radius: 20px;
        }
        
        .slider-content {
            position: relative;
            z-index: 1;
        }
        
        .slider-group.slider1 {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        }
        
        .slider-group.slider2 {
            background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
        }
        
        .slider-label {
            font-size: 1.4em;
            font-weight: bold;
            margin-bottom: 20px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
        }
        
        .slider-wrapper {
            position: relative;
            margin: 20px 0;
        }
        
        .slider {
            width: 100%;
            height: 8px;
            border-radius: 4px;
            background: rgba(255,255,255,0.3);
            outline: none;
            appearance: none;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        
        .slider::-webkit-slider-thumb {
            appearance: none;
            width: 24px;
            height: 24px;
            border-radius: 50%;
            background: white;
            cursor: pointer;
            border: 3px solid rgba(255,255,255,0.8);
            box-shadow: 0 2px 10px rgba(0,0,0,0.2);
            transition: all 0.2s ease;
        }
        
        .slider::-webkit-slider-thumb:hover {
            transform: scale(1.2);
            box-shadow: 0 4px 20px rgba(0,0,0,0.3);
        }
        
        .slider::-moz-range-thumb {
            width: 24px;
            height: 24px;
            border-radius: 50%;
            background: white;
            cursor: pointer;
            border: 3px solid rgba(255,255,255,0.8);
            box-shadow: 0 2px 10px rgba(0,0,0,0.2);
        }
        
        .value-display {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-top: 15px;
            font-size: 1.1em;
        }
        
        .current-value {
            font-size: 2em;
            font-weight: bold;
            text-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        
        .range-labels {
            display: flex;
            justify-content: space-between;
            font-size: 0.9em;
            opacity: 0.8;
            margin-top: 5px;
        }
        
        .preset-buttons {
            display: flex;
            gap: 10px;
            margin-top: 20px;
            flex-wrap: wrap;
            justify-content: center;
        }
        
        .preset-btn {
            background: rgba(255,255,255,0.2);
            color: white;
            border: 1px solid rgba(255,255,255,0.3);
            border-radius: 15px;
            padding: 8px 16px;
            cursor: pointer;
            font-size: 0.9em;
            transition: all 0.2s;
        }
        
        .preset-btn:hover {
            background: rgba(255,255,255,0.3);
            transform: translateY(-1px);
        }
        
        .controls-panel {
            background: #f8f9fa;
            border-radius: 15px;
            padding: 25px;
            margin-bottom: 30px;
        }
        
        .controls-title {
            font-size: 1.2em;
            font-weight: bold;
            color: #333;
            margin-bottom: 20px;
        }
        
        .control-buttons {
            display: flex;
            gap: 15px;
            justify-content: center;
            flex-wrap: wrap;
        }
        
        /* Desktop Styles (Large screens) */
        @media (min-width: 1024px) {
            .container {
                padding: 60px;
            }
            
            .header h1 {
                font-size: 3.5em;
            }
            
            .sliders-container {
                flex-direction: row;
                gap: 60px;
                justify-content: center;
                align-items: stretch;
            }
            
            .slider-group {
                flex: 1;
                max-width: 400px;
                padding: 40px;
            }
            
            .preset-buttons {
                gap: 12px;
            }
            
            .preset-btn {
                padding: 10px 18px;
                font-size: 0.9em;
                min-width: 60px;
            }
            
            .connection-status {
                font-size: 1.1em;
            }
            
            .slider-title {
                font-size: 1.4em;
            }
            
            .value-display {
                margin: 20px 0;
            }
            
            .current-value {
                font-size: 2.2em;
            }
        }
        
        /* Tablet Styles (Medium screens) */
        @media (min-width: 769px) and (max-width: 1023px) {
            .container {
                padding: 50px;
                max-width: 900px;
            }
            
            .header h1 {
                font-size: 3em;
            }
            
            .sliders-container {
                flex-direction: row;
                gap: 40px;
                justify-content: center;
            }
            
            .slider-group {
                flex: 1;
                max-width: 350px;
                padding: 35px;
            }
            
            .preset-buttons {
                gap: 10px;
            }
            
            .preset-btn {
                padding: 9px 16px;
                font-size: 0.85em;
            }
            
            .current-value {
                font-size: 2em;
            }
        }
        
        /* Mobile Styles (Small screens) */
        @media (max-width: 768px) {
            body {
                padding-bottom: 50px;
            }
            
            .container {
                padding: 20px 20px 30px 20px;
            }
            
            .top-nav {
                margin: -20px -20px 0 -20px;
            }
            
            .home-nav {
                margin: -20px -20px 20px -20px;
                padding: 8px 15px;
            }
            
            .home-link {
                font-size: 1em;
                padding: 6px 10px;
            }
            
            .header h1 {
                font-size: 2em;
            }
            
            .sliders-container {
                gap: 30px;
            }
            
            .slider-group {
                padding: 20px;
            }
            
            .preset-buttons {
                gap: 5px;
            }
            
            .preset-btn {
                padding: 6px 12px;
                font-size: 0.8em;
            }
            
            .control-buttons {
                flex-direction: column;
                align-items: center;
            }
            
            .footer {
                height: 50px;
                padding: 10px 15px;
                font-size: 0.8em;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="top-nav">
            <a href="/" class="home-link">🏠 Home</a>
            <a href="https://diyables.io/webapps-r4" class="tutorial-link" target="_blank">📚 Tutorial</a>
        </div>
        <div class="websocket-status" id="websocketStatus">
            WebSocket: <span id="connectionText">Disconnected</span>
        </div>
        <div class="header">
            <h1><span class="emoji">🎚️</span> <span class="text">Remote Slider</span></h1>
            <p>Control Arduino with dual range sliders</p>
        </div>
        
        <div style="flex: 1;">
        
        <div class="sliders-container">
            <div class="slider-group slider1">
                <div class="slider-content">
                    <div class="slider-label">
                        <span>🔵 Slider 1</span>
                    </div>
                    <div class="slider-wrapper">
                        <input type="range" min="0" max="255" value="0" class="slider" id="slider1">
                        <div class="value-display">
                            <div>Value:</div>
                            <div class="current-value" id="value1">0</div>
                        </div>
                        <div class="range-labels">
                            <span>0</span>
                            <span>255</span>
                        </div>
                    </div>
                    <div class="preset-buttons">
                        <button class="preset-btn" onclick="setSlider1(0)">Min</button>
                        <button class="preset-btn" onclick="setSlider1(64)">25%</button>
                        <button class="preset-btn" onclick="setSlider1(128)">50%</button>
                        <button class="preset-btn" onclick="setSlider1(192)">75%</button>
                        <button class="preset-btn" onclick="setSlider1(255)">Max</button>
                    </div>
                </div>
            </div>
            
            <div class="slider-group slider2">
                <div class="slider-content">
                    <div class="slider-label">
                        <span>Slider 2</span>
                    </div>
                    <div class="slider-wrapper">
                        <input type="range" min="0" max="255" value="0" class="slider" id="slider2">
                        <div class="value-display">
                            <div>Value:</div>
                            <div class="current-value" id="value2">0</div>
                        </div>
                        <div class="range-labels">
                            <span>0</span>
                            <span>255</span>
                        </div>
                    </div>
                    <div class="preset-buttons">
                        <button class="preset-btn" onclick="setSlider2(0)">Min</button>
                        <button class="preset-btn" onclick="setSlider2(64)">25%</button>
                        <button class="preset-btn" onclick="setSlider2(128)">50%</button>
                        <button class="preset-btn" onclick="setSlider2(192)">75%</button>
                        <button class="preset-btn" onclick="setSlider2(255)">Max</button>
                    </div>
                </div>
            </div>
        </div>
    </div>
    </div>
    
    <script>
        let ws = null;
        let isConnected = false;
        let slider1Value = 0;
        let slider2Value = 0;
        let sendTimeout = null;
        let initialValuesReceived = false;
        
        const slider1 = document.getElementById('slider1');
        const slider2 = document.getElementById('slider2');
        const value1 = document.getElementById('value1');
        const value2 = document.getElementById('value2');
        const connectionText = document.getElementById('connectionText');
        const websocketStatus = document.getElementById('websocketStatus');
        
        // Log initialization
        console.log('Remote Slider initialized at', new Date().toLocaleTimeString());
        
        function connect() {
            if (ws && ws.readyState === WebSocket.OPEN) {
                return;
            }
            
            const wsUrl = 'ws://' + window.location.hostname + ':81';
            console.log('Connecting to ' + window.location.hostname + '...');
            
            ws = new WebSocket(wsUrl);
            
            ws.onopen = function() {
                isConnected = true;
                updateConnectionStatus('connected');
                console.log('Connected to Arduino Remote Slider!');
                
                // Request initial slider values from Arduino
                ws.send('SLIDER:GET_VALUES');
                console.log('Requesting initial slider values...');
                
                // Only send current values if no response received after 2 seconds
                setTimeout(function() {
                    if (!initialValuesReceived) {
                        console.log('No initial values received, sending current values...');
                        sendCurrentValues();
                    }
                }, 2000);
            };
            
            ws.onmessage = function(event) {
                console.log('Arduino: ' + event.data);
                
                // Parse response for slider state updates
                parseArduinoResponse(event.data);
            };
            
            ws.onclose = function() {
                isConnected = false;
                initialValuesReceived = false; // Reset flag on disconnect
                updateConnectionStatus('disconnected');
                console.log('Connection lost. Attempting to reconnect...');
                
                // Auto-reconnect after 3 seconds
                setTimeout(connect, 3000);
            };
            
            ws.onerror = function(error) {
                console.log('Connection error occurred');
                console.error('WebSocket error:', error);
            };
        }
        
        function updateConnectionStatus(status) {
            const connectionText = document.getElementById('connectionText');
            connectionText.textContent = status;
            console.log('WebSocket ' + status);
            
            if(status == 'connected')
                connectionText.style.color = '#007bff';
            else if(status == 'connecting')
                connectionText.style.color = '#6c757d';
            else
                connectionText.style.color = '#dc3545';
        }
        
        function updateSliderDisplay(sliderNum, value) {
            if (sliderNum === 1) {
                slider1Value = value;
                value1.textContent = value;
                slider1.value = value;
            } else {
                slider2Value = value;
                value2.textContent = value;
                slider2.value = value;
            }
        }
        
        function sendSliderValues() {
            if (ws && ws.readyState === WebSocket.OPEN) {
                const message = 'SLIDER:' + slider1Value + ',' + slider2Value;
                ws.send(message);
                console.log('Sent: Slider1=' + slider1Value + ', Slider2=' + slider2Value);
            }
        }
        
        function debouncedSend() {
            clearTimeout(sendTimeout);
            sendTimeout = setTimeout(sendSliderValues, 100); // Send after 100ms of no changes
        }
        
        function setSlider1(value) {
            updateSliderDisplay(1, value);
            debouncedSend();
        }
        
        function setSlider2(value) {
            updateSliderDisplay(2, value);
            debouncedSend();
        }
        
        function parseArduinoResponse(response) {
            // Handle initial slider values response - format: SLIDER_VALUES:50,75
            if (response.startsWith('SLIDER_VALUES:')) {
                const valuesStr = response.substring(14); // Remove "SLIDER_VALUES:" prefix
                const values = valuesStr.split(',');
                
                if (values.length === 2) {
                    const value1 = parseInt(values[0]);
                    const value2 = parseInt(values[1]);
                    
                    if (!isNaN(value1) && !isNaN(value2)) {
                        // Update sliders without triggering send
                        updateSliderDisplayOnly(1, value1);
                        updateSliderDisplayOnly(2, value2);
                        console.log('Initial slider values received: Slider1=' + value1 + ', Slider2=' + value2);
                        initialValuesReceived = true;
                    }
                }
                return;
            }
            
            // Handle slider value updates from Arduino
            if (response.startsWith('SLIDER:')) {
                const valuesStr = response.substring(7); // Remove "SLIDER:" prefix
                const values = valuesStr.split(',');
                
                if (values.length === 2) {
                    const value1 = parseInt(values[0]);
                    const value2 = parseInt(values[1]);
                    
                    if (!isNaN(value1) && !isNaN(value2)) {
                        // Update sliders without triggering send
                        updateSliderDisplayOnly(1, value1);
                        updateSliderDisplayOnly(2, value2);
                        console.log('Slider values updated from Arduino: Slider1=' + value1 + ', Slider2=' + value2);
                    }
                }
            }
        }
        
        function updateSliderDisplayOnly(sliderNum, value) {
            // Update slider display without triggering WebSocket send
            if (sliderNum === 1) {
                slider1Value = value;
                document.getElementById('slider1').value = value;
                document.getElementById('value1').textContent = value;
            } else if (sliderNum === 2) {
                slider2Value = value;
                document.getElementById('slider2').value = value;
                document.getElementById('value2').textContent = value;
            }
        }
        
        function sendCurrentValues() {
            if (isConnected) {
                sendSliderValues();
            }
        }
        
        // Event listeners for sliders
        slider1.addEventListener('input', function() {
            updateSliderDisplay(1, parseInt(this.value));
            debouncedSend();
        });
        
        slider2.addEventListener('input', function() {
            updateSliderDisplay(2, parseInt(this.value));
            debouncedSend();
        });
        
        // Auto-connect on page load
        window.addEventListener('load', function() {
            setTimeout(connect, 500);
        });
        
        // Handle page visibility change
        document.addEventListener('visibilitychange', function() {
            if (!document.hidden && (!ws || ws.readyState !== WebSocket.OPEN)) {
                setTimeout(connect, 1000);
            }
        });
    </script>
    
    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>
</body>
</html>
)HTMLDELIM";

#endif
