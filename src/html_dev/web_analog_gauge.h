#ifndef WEB_ANALOG_GAUGE_HTML_H
#define WEB_ANALOG_GAUGE_HTML_H

const char WEB_ANALOG_GAUGE_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Analog Gauge - DIYables WebApp</title>
    <link rel="icon" href="https://diyables.io/images/page/diyables.svg">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            min-height: 100vh;
            margin: 0;
            padding: 0 0 40px 0;
            display: flex;
            flex-direction: column;
            text-align: center;
        }
        
        .container {
            background: white;
            border-radius: 0;
            box-shadow: none;
            width: 100%;
            flex: 1;
            max-width: 800px;
            margin: 0 auto;
            text-align: center;
            display: flex;
            flex-direction: column;
            justify-content: flex-start;
        }
        
        .header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 25px;
            text-align: center;
            position: relative;
        }
        
        .header h1 {
            font-size: 2.0em;
            margin-bottom: 5px;
        }
        
        .header p {
            font-size: 1.0em;
            opacity: 0.9;
        }
        
        .top-nav {
            background: #f8f9fa;
            padding: 10px 20px;
            border-bottom: 1px solid #e9ecef;
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
        
        .gauge-area {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 20px;
            margin: 20px 0;
        }
        
        #gauge_canvas {
            border-radius: 50%;
            box-shadow: 0 4px 20px rgba(0,0,0,0.15);
        }
        
        .gauge-info {
            display: flex;
            gap: 20px;
            justify-content: center;
            align-items: center;
            flex-wrap: wrap;
            margin-top: 20px;
        }
        
        .gauge-info > span {
            background: white;
            padding: 8px 12px;
            border-radius: 6px;
            border: 1px solid #dee2e6;
        }
        
        .gauge-info span span {
            background: none;
            padding: 0;
            border-radius: 0;
            border: none;
            color: #007bff;
        }
        
        @media (max-width: 768px) {
            .header h1 {
                font-size: 1.6em;
            }
            
            .controls {
                flex-direction: column;
                gap: 10px;
            }
            
            .gauge-info {
                flex-direction: column;
                gap: 10px;
            }
            
            #gauge_canvas {
                max-width: 300px;
                max-height: 300px;
                width: 100%;
                height: auto;
            }
            
            .footer {
                height: 50px;
                padding: 10px 15px;
                font-size: 0.8em;
            }
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
            <h1>⏲️ Analog Gauge</h1>
            <p>Real-time analog gauge visualization</p>
        </div>
        
        <div class="gauge-area">
            <div class="gauge-container">
                <canvas id="gauge_canvas"></canvas>
            </div>
            
            <div class="gauge-info">
                <span>Value: <span id="currentValue">0</span></span>
                <span>Range: <span id="gaugeMin">0</span> - <span id="gaugeMax">100</span></span>
            </div>
        </div>
    </div>

    <script>
        var canvas_width = 450, canvas_height = 450;
        var pivot_x = canvas_width/2, pivot_y = canvas_height/2;
        var pivot_radius = 7;
        var hand_radius = 95, hand_max_angle = 280;
        var ws = null;
        var currentAngle = 0;
        var currentValue = 0;
        var minValue = 0, maxValue = 100; // Default range
        var unit = ''; // Default no unit

        function init() {
            var gauge = document.getElementById("gauge_canvas");
            var ctx = gauge.getContext("2d");

            gauge.width = canvas_width;
            gauge.height = canvas_height;

            ctx.translate(pivot_x, pivot_y);
            ctx.rotate(130 / 180 * Math.PI);
            ctx.shadowColor = "LightGray";
            
            updateGaugeView(0);
            
            // Auto-connect after 500ms like other apps
            setTimeout(connectWebSocket, 500);
        }

        function connectWebSocket() {
            try {
                const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
                const wsUrl = protocol + '//' + window.location.hostname + ':81';
                ws = new WebSocket(wsUrl);
                
                updateConnectionStatus('connecting');
                
                ws.onopen = function() {
                    updateConnectionStatus('connected');
                    
                    // Request gauge configuration and initial value
                    ws.send('GAUGE:GET_CONFIG');
                    ws.send('GAUGE:REQUEST_VALUE');
                };
                
                ws.onclose = function() {
                    updateConnectionStatus('disconnected');
                    ws = null;
                };
                
                ws.onmessage = function(event) {
                    try {
                        // Handle gauge configuration response - format: GAUGE_CONFIG:{"minValue":0.0,"maxValue":100.0,"unit":"°C"}
                        if (event.data.startsWith('GAUGE_CONFIG:')) {
                            const configStr = event.data.substring(13); // Remove "GAUGE_CONFIG:" prefix
                            const config = JSON.parse(configStr);
                            
                            if (config.minValue !== undefined && config.maxValue !== undefined) {
                                unit = config.unit || '';
                                updateGaugeConfig(config.minValue, config.maxValue, unit);
                                console.log('Gauge config received: min=' + config.minValue + ', max=' + config.maxValue + ', unit=' + unit);
                            }
                            return;
                        }
                        
                        // Handle gauge value response - format: GAUGE_VALUE:90.5
                        if (event.data.startsWith('GAUGE_VALUE:')) {
                            const valueStr = event.data.substring(12); // Remove "GAUGE_VALUE:" prefix
                            const value = parseFloat(valueStr);
                            
                            if (!isNaN(value)) {
                                updateGaugeView(value);
                                console.log('Gauge value received: ' + value + ' ' + unit);
                            }
                            return;
                        }
                        
                        // Try parsing as plain number for backwards compatibility
                        const angle = parseFloat(event.data);
                        if (!isNaN(angle)) {
                            updateGaugeView(angle);
                        }
                    } catch (e) {
                        console.error('Error parsing gauge data:', e);
                    }
                };
                
                ws.onerror = function(error) {
                    console.error('WebSocket error:', error);
                };
                
            } catch (error) {
                console.error('Failed to create WebSocket:', error);
                updateConnectionStatus('disconnected');
            }
        }

        function disconnectWebSocket() {
            if (ws) {
                ws.close();
            }
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

        function updateGaugeConfig(min, max, unitParam) {
            minValue = min;
            maxValue = max;
            unit = unitParam; // Update the global unit variable
            
            // Update display to show the new range with unit
            const unitStr = unit ? unit : '';
            document.getElementById('gaugeMin').textContent = min.toFixed(1) + unitStr;
            document.getElementById('gaugeMax').textContent = max.toFixed(1) + unitStr;
            
            // Update the current value display to include unit
            const currentValueText = document.getElementById('currentValue').textContent;
            if (currentValueText && !isNaN(parseFloat(currentValueText))) {
                const numValue = parseFloat(currentValueText);
                document.getElementById('currentValue').textContent = numValue.toFixed(1) + unitStr;
            }
            
            // Redraw gauge with current angle to reflect new boundaries
            redrawGauge();
        }

        function redrawGauge() {
            // Redraw the gauge with the current stored value
            updateGaugeView(currentValue);
        }

        function updateGaugeView(value) {
            // Store the current value
            currentValue = value;
            
            // Convert value to angle based on min/max range
            var angle = ((value - minValue) / (maxValue - minValue)) * hand_max_angle;
            
            // Clamp angle to valid range
            if (angle < 0) angle = 0;
            if (angle > hand_max_angle) angle = hand_max_angle;
            
            var gauge = document.getElementById("gauge_canvas");
            var ctx = gauge.getContext("2d");
            
            currentAngle = angle;
            // Display the actual value with unit, not the angle
            document.getElementById('currentValue').textContent = value.toFixed(1) + unit;
            
            // Clear canvas
            ctx.save();
            ctx.setTransform(1, 0, 0, 1, 0, 0);
            ctx.clearRect(0, 0, canvas_width, canvas_height);
            ctx.restore();
            
            ctx.shadowBlur = 15;
            ctx.fillStyle = "#808080";
            ctx.beginPath();
            ctx.arc(0, 0, 215, 0, 2 * Math.PI);
            ctx.fill();
            
            ctx.fillStyle = "#808080";
            ctx.strokeStyle = "#bfbfbf";
            ctx.lineWidth = 3;
            ctx.beginPath();
            ctx.arc(0, 0, 200, 0, 2 * Math.PI);
            ctx.fill();
            ctx.stroke();
            
            ctx.shadowBlur = 1;
            ctx.fillStyle = "#383330";
            ctx.beginPath();
            ctx.arc(0, 0, 180, 0, 2 * Math.PI);
            ctx.fill();
            
            ctx.fillStyle = "black";
            ctx.beginPath();
            ctx.arc(0, 0, 165, 0, 2 * Math.PI);
            ctx.fill();
            
            ctx.strokeStyle = "white";
            ctx.fillStyle = "white";
            ctx.shadowBlur = 20;
            ctx.shadowColor = "white";
            ctx.save();
            
            // Major tick marks
            ctx.lineWidth = 10;
            for (var i = 0; i < 5; i++) {
                ctx.beginPath();
                ctx.lineTo(hand_radius + 12, 0);
                ctx.lineTo(hand_radius + 50, 0);
                ctx.stroke();
                ctx.rotate(70 / 180 * Math.PI);
            }
            ctx.restore();
            ctx.save();
            
            // Medium tick marks
            ctx.rotate(35 / 180 * Math.PI);
            ctx.lineWidth = 8;
            for (var i = 0; i < 4; i++) {
                ctx.beginPath();
                ctx.lineTo(hand_radius + 12, 0);
                ctx.lineTo(hand_radius + 40, 0);
                ctx.stroke();
                ctx.rotate(70 / 180 * Math.PI);
            }
            ctx.restore();
            ctx.save();
            
            // Minor tick marks
            ctx.rotate(17.5 / 180 * Math.PI);
            ctx.lineWidth = 7;
            for (var i = 0; i < 8; i++) {
                ctx.beginPath();
                ctx.lineTo(hand_radius + 12, 0);
                ctx.lineTo(hand_radius + 35, 0);
                ctx.stroke();
                ctx.rotate(35 / 180 * Math.PI);
            }
            
            ctx.restore();
            ctx.lineCap = "round";
            ctx.lineWidth = 7;
            
            // Draw gauge hand
            ctx.save();
            ctx.rotate(angle / 180 * Math.PI);
            ctx.strokeStyle = "#ff4444";
            ctx.fillStyle = "#ff4444";
            ctx.beginPath();
            ctx.lineTo(0, 0);
            ctx.lineTo(hand_radius, 0);
            ctx.stroke();
            ctx.restore();
            
            // Center pivot
            ctx.beginPath();
            ctx.arc(0, 0, 10, 0, 2 * Math.PI);
            ctx.fill();
            
            // Display value on gauge
            ctx.save();
            ctx.rotate(-130 / 180 * Math.PI);
            ctx.font = "24px Arial";
            ctx.textAlign = "center";
            ctx.fillStyle = "white";
            ctx.fillText(value.toFixed(1) + unit, 0, 50);
            ctx.restore();
        }

        window.onload = init;
        
        // Handle page visibility change for auto-reconnect
        document.addEventListener('visibilitychange', function() {
            if (!document.hidden && (!ws || ws.readyState !== WebSocket.OPEN)) {
                setTimeout(connectWebSocket, 1000);
            }
        });
    </script>
    
    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>
</body>
</html>
)HTMLDELIM";

#endif
