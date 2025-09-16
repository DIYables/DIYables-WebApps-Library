#ifndef WEB_TEMPERATURE_H
#define WEB_TEMPERATURE_H

const char HTML_CONTENT_TEMPERATURE[] PROGMEM = R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Temperature - DIYables</title>
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
            color: #333;
            font-size: 2.5em;
            margin: 0;
            font-weight: 700;
        }
        
        .top-nav {
            background: #f8f9fa;
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
            margin: 0 -40px 20px -40px;
            text-align: center;
            font-size: 0.9em;
            color: black;
        }
        
        .websocket-status #connectionText {
            font-weight: bold;
        }
        
        .content {
            flex: 1;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            min-height: calc(100vh - 200px);
        }
        
        @media (max-width: 768px) {
            .container {
                padding: 20px;
            }
            
            .header h1 {
                font-size: 1.6em;
            }
            
            .top-nav {
                padding-top: 15px;
            }
            
            .websocket-status {
                margin: 0 -20px 20px -20px;
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
            <a href="https://diyables.io/webapps-r4" target="_blank" class="tutorial-link">📚 Tutorial</a>
        </div>
        
        <div class="websocket-status">
            WebSocket: <span id="connectionText">Disconnected</span>
        </div>
        
        <div class="header">
            <h1>🌡️ Web Temperature</h1>
        </div>
        
        <div class="content">
            <div class="temperature-container">
                <canvas id="temperature_canvas"></canvas>
            </div>
        </div>
    </div>

    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>

    <script>
        var canvas_width = 200, canvas_height = 450;
        var ws = null;
        var minValue = 0, maxValue = 100;
        var unit = "°C";
        var currentTemperature = 0;

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

        window.onload = function() {
            var canvas = document.getElementById("temperature_canvas");
            canvas.width = canvas_width;
            canvas.height = canvas_height;
            
            var ctx = canvas.getContext("2d");
            ctx.translate(canvas_width/2, canvas_height - 80);
            
            updateTemperatureView(0);
            
            // Auto-connect after 500ms like other apps
            setTimeout(connectWebSocket, 500);
        };

        function connectWebSocket() {
            const wsProtocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
            const wsUrl = `${wsProtocol}//${window.location.hostname}:81`;
            
            try {
                ws = new WebSocket(wsUrl);
                
                ws.onopen = function() {
                    updateConnectionStatus('connected');
                    
                    // Request temperature configuration and initial value
                    ws.send('TEMP:GET_CONFIG');
                    ws.send('TEMP:REQUEST_VALUE');
                };
                
                ws.onclose = function() {
                    updateConnectionStatus('disconnected');
                    ws = null;
                };
                
                ws.onmessage = function(event) {
                    try {
                        // Handle temperature configuration response - format: TEMP_CONFIG:{"minValue":0.0,"maxValue":100.0,"unit":"°C"}
                        if (event.data.startsWith('TEMP_CONFIG:')) {
                            const configData = JSON.parse(event.data.substring(12));
                            updateTemperatureConfig(configData.minValue, configData.maxValue, configData.unit);
                            return;
                        }
                        
                        // Handle temperature value response - format: TEMP_VALUE:{"value":25.5,"unit":"°C"}
                        if (event.data.startsWith('TEMP_VALUE:')) {
                            const tempData = JSON.parse(event.data.substring(11));
                            const value = parseFloat(tempData.value);
                            
                            if (!isNaN(value)) {
                                updateTemperatureView(value);
                                console.log('Temperature received: ' + value + ' ' + unit);
                            }
                            return;
                        }
                        
                        // Try parsing as plain number for backwards compatibility
                        const temp = parseFloat(event.data);
                        if (!isNaN(temp)) {
                            updateTemperatureView(temp);
                        }
                    } catch (e) {
                        console.error('Error parsing message:', e);
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

        function updateTemperatureConfig(min, max, unitParam) {
            minValue = min;
            maxValue = max;
            unit = unitParam; // Update the global unit variable
            
            // Redraw thermometer with new range
            updateTemperatureView(currentTemperature);
        }

        function updateTemperatureView(temp) {
            currentTemperature = temp;
            
            var canvas = document.getElementById("temperature_canvas");
            var ctx = canvas.getContext("2d");
            
            var radius = 70;
            var offset = 5;
            var width = 45;
            var height = 330;
         
            ctx.clearRect(-canvas_width/2, -350, canvas_width, canvas_height);
            
            // Set colors based on connection status
            if(ws != null) {
                ctx.strokeStyle = "#667eea";
                ctx.fillStyle = "#667eea";
            } else {
                ctx.strokeStyle = "#bbb";
                ctx.fillStyle = "#bbb";
            }
            
            // Calculate temperature percentage based on range
            var tempPercent = ((temp - minValue) / (maxValue - minValue)) * 100;
            tempPercent = Math.max(0, Math.min(100, tempPercent)); // Clamp between 0-100
            
            // Draw scale marks - 5-step
            var x = -width/2;
            ctx.lineWidth = 2;
            for (var i = 0; i <= 100; i += 5) {
                var y = -(height - radius) * i / 100 - radius - 5;
                ctx.beginPath();
                ctx.lineTo(x, y);
                ctx.lineTo(x - 20, y);
                ctx.stroke();
            }
            
            // Draw scale marks - 20-step with labels
            ctx.lineWidth = 5;
            for (var i = 0; i <= 100; i += 20) {
                var y = -(height - radius) * i / 100 - radius - 5;
                ctx.beginPath();
                ctx.lineTo(x, y);
                ctx.lineTo(x - 25, y);
                ctx.stroke();
                
                // Calculate actual temperature value for this mark
                var scaleTemp = minValue + (maxValue - minValue) * i / 100;
                
                ctx.font = "16px Georgia";
                ctx.textBaseline = "middle"; 
                ctx.textAlign = "right";
                ctx.fillText(scaleTemp.toFixed(0), x - 35, y);
            }
            
            // Draw thermometer outline
            ctx.lineWidth = 16;
            ctx.beginPath();
            ctx.arc(0, 0, radius, 0, 2 * Math.PI);
            ctx.stroke();
            
            ctx.beginPath();
            ctx.rect(-width/2, -height, width, height); 
            ctx.stroke();
            
            ctx.beginPath();
            ctx.arc(0, -height, width/2, 0, 2 * Math.PI);
            ctx.stroke();
            
            // Fill thermometer background
            ctx.fillStyle = "#f8f9fa";
            ctx.beginPath();
            ctx.arc(0, 0, radius, 0, 2 * Math.PI);
            ctx.fill();
            
            ctx.beginPath();
            ctx.rect(-width/2, -height, width, height); 
            ctx.fill();
            
            ctx.beginPath();
            ctx.arc(0, -height, width/2, 0, 2 * Math.PI);
            ctx.fill();
            
            // Draw temperature value (mercury with gradient effect)
            if(ws != null) {
                // Create gradient for mercury
                var gradient = ctx.createLinearGradient(0, -height, 0, radius);
                gradient.addColorStop(0, "#ff6b6b");
                gradient.addColorStop(0.5, "#ff5252");
                gradient.addColorStop(1, "#f44336");
                ctx.fillStyle = gradient;
            } else {
                ctx.fillStyle = "#bbb";
            }
                
            ctx.beginPath();
            ctx.arc(0, 0, radius - offset, 0, 2 * Math.PI);
            ctx.fill();
            
            var y = (height - radius) * tempPercent / 100.0 + radius + 5; 
            ctx.beginPath();
            ctx.rect(-width/2 + offset, -y, width - 2*offset, y); 
            ctx.fill();
            
            // Draw temperature text in the bulb
            if(ws != null) {
                ctx.fillStyle = "white";
                ctx.font = "bold 24px Georgia";
                ctx.textBaseline = "middle"; 
                ctx.textAlign = "center";
                ctx.fillText(temp.toFixed(1) + unit, 0, 0);
            }
        }
    </script>
</body>
</html>
)";

#endif
