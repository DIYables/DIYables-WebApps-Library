#ifndef WEB_ROTATOR_HTML_H
#define WEB_ROTATOR_HTML_H

const char WEB_ROTATOR_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Remote Rotator - DIYables WebApp</title>
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
            text-align: center;
            display: flex;
            flex-direction: column;
            justify-content: flex-start;
            box-sizing: border-box;
            overflow: hidden;
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
        
        .controls {
            padding: 40px;
            margin-bottom: 30px;
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 30px;
        }
        
        .rotator-container {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 20px;
        }
        
        .disc {
            width: 300px;
            height: 300px;
            border-radius: 50%;
            background: conic-gradient(#4f46e5 0% 25%, #16a34a 25% 50%, #ef4444 50% 75%, #facc15 75% 100%);
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
            cursor: grab;
            transition: box-shadow 0.2s ease;
            position: relative;
            border: 3px solid #fff;
        }
        
        .disc:active {
            cursor: grabbing;
            box-shadow: 0 10px 40px rgba(0,0,0,0.3);
        }
        
        .disc::before {
            content: '';
            position: absolute;
            top: 10px;
            left: 50%;
            transform: translateX(-50%);
            width: 4px;
            height: 20px;
            background: #fff;
            border-radius: 2px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.3);
        }
        
        .angle-display {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 10px;
        }
        
        .angle-label {
            font-size: 2.5em;
            font-weight: 700;
            color: #2D3748;
            font-family: 'Courier New', monospace;
        }
        
        .rotator-info {
            display: flex;
            flex-wrap: wrap;
            justify-content: center;
            gap: 20px;
            margin-top: 20px;
        }
        
        .info-item {
            background: white;
            padding: 15px 20px;
            border-radius: 15px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            border: 1px solid #e2e8f0;
            min-width: 120px;
        }
        
        .info-label {
            font-size: 0.9em;
            color: #718096;
            margin-bottom: 5px;
        }
        
        .info-value {
            font-size: 1.2em;
            font-weight: 600;
            color: #2D3748;
        }
        
        @media (max-width: 768px) {
            .header h1 {
                font-size: 1.6em;
            }
            
            .controls {
                flex-direction: column;
                gap: 20px;
                padding: 20px;
            }
            
            .rotator-info {
                flex-direction: row;
                flex-wrap: wrap;
                gap: 8px;
                justify-content: center;
            }
            
            .info-item {
                min-width: auto;
                flex: 1;
                max-width: none;
                padding: 10px 12px;
                white-space: nowrap;
            }
            
            .info-label {
                font-size: 0.8em;
                margin-bottom: 3px;
            }
            
            .info-value {
                font-size: 0.9em;
                white-space: nowrap;
            }
            
            .disc {
                width: 250px;
                height: 250px;
            }
            
            .angle-label {
                font-size: 2em;
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
        
        <div class="websocket-status" id="websocketStatus">
            WebSocket: <span id="connectionText">Disconnected</span>
        </div>
        
        <div class="header">
            <h1>🔄 Remote Rotator</h1>
            <p>Interactive rotatable disc real-time control</p>
        </div>
        
        <div style="flex: 1;">
            <div class="controls">
                <div class="rotator-container">
                    <div class="disc" id="disc"></div>
                    <div class="angle-display">
                        <div class="angle-label" id="angle-label">0°</div>
                    </div>
                </div>
                
                <div class="rotator-info">
                    <div class="info-item">
                        <div class="info-label">Mode</div>
                        <div class="info-value" id="mode-display">Continuous</div>
                    </div>
                    <div class="info-item" id="angle-range-item" style="display: none;">
                        <div class="info-label">Angle Range</div>
                        <div class="info-value" id="angle-range">0° - 180°</div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <script>
        const disc = document.getElementById('disc');
        const angleLabel = document.getElementById('angle-label');
        const modeDisplay = document.getElementById('mode-display');
        const angleRangeItem = document.getElementById('angle-range-item');
        const angleRangeDisplay = document.getElementById('angle-range');
        
        let isDragging = false;
        let center = null;
        let currentAngle = 0;
        let totalRotation = 0;
        let lastAngle = null;
        let rotatorMode = 0; // 0 = continuous, 1 = limited
        let minAngle = 0;
        let maxAngle = 360;
        let ws = null;

        function getAngle(x, y) {
            const dx = x - center.x;
            const dy = y - center.y;
            return Math.atan2(dy, dx) * (180/Math.PI);
        }

        function updateAngleDisplay(angle) {
            const displayAngle = Math.round(angle);
            angleLabel.textContent = `${displayAngle}°`;
            disc.style.transform = `rotate(${angle}deg)`;
        }

        function updateModeDisplay() {
            if (rotatorMode === 1) { // Limited mode
                modeDisplay.textContent = 'Limited';
                angleRangeItem.style.display = 'block';
                angleRangeDisplay.textContent = `${minAngle}° - ${maxAngle}°`;
            } else { // Continuous mode
                modeDisplay.textContent = 'Continuous';
                angleRangeItem.style.display = 'none';
            }
        }

        function applyAngleLimits(angle) {
            if (rotatorMode === 1) { // Limited mode
                if (angle < minAngle) return minAngle;
                if (angle > maxAngle) return maxAngle;
            }
            return angle;
        }

        function sendAngleToArduino(angle) {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(`ROTATOR:${angle.toFixed(1)}`);
            }
        }

        // Mouse events
        disc.addEventListener('mousedown', e => {
            isDragging = true;
            const rect = disc.getBoundingClientRect();
            center = { x: rect.left + rect.width/2, y: rect.top + rect.height/2 };
            lastAngle = getAngle(e.clientX, e.clientY);
        });

        window.addEventListener('mousemove', e => {
            if (!isDragging) return;
            const angle = getAngle(e.clientX, e.clientY);

            if (lastAngle !== null) {
                let delta = angle - lastAngle;
                if (delta > 180) delta -= 360;
                if (delta < -180) delta += 360;
                
                let newRotation = totalRotation + delta;
                newRotation = applyAngleLimits(newRotation);
                
                if (newRotation !== totalRotation) {
                    totalRotation = newRotation;
                    updateAngleDisplay(totalRotation);
                    sendAngleToArduino(totalRotation);
                }
            }

            lastAngle = angle;
        });

        window.addEventListener('mouseup', () => {
            isDragging = false;
            lastAngle = null;
        });

        // Touch events for mobile
        disc.addEventListener('touchstart', e => {
            e.preventDefault();
            isDragging = true;
            const rect = disc.getBoundingClientRect();
            center = { x: rect.left + rect.width/2, y: rect.top + rect.height/2 };
            const touch = e.touches[0];
            lastAngle = getAngle(touch.clientX, touch.clientY);
        }, { passive: false });

        window.addEventListener('touchmove', e => {
            if (!isDragging) return;
            e.preventDefault();
            const touch = e.touches[0];
            const angle = getAngle(touch.clientX, touch.clientY);

            if (lastAngle !== null) {
                let delta = angle - lastAngle;
                if (delta > 180) delta -= 360;
                if (delta < -180) delta += 360;
                
                let newRotation = totalRotation + delta;
                newRotation = applyAngleLimits(newRotation);
                
                if (newRotation !== totalRotation) {
                    totalRotation = newRotation;
                    updateAngleDisplay(totalRotation);
                    sendAngleToArduino(totalRotation);
                }
            }

            lastAngle = angle;
        }, { passive: false });

        window.addEventListener('touchend', () => {
            isDragging = false;
            lastAngle = null;
        });

        // WebSocket functions
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

        function connectWebSocket() {
            const wsProtocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
            const wsUrl = `${wsProtocol}//${window.location.hostname}:81`;
            
            try {
                ws = new WebSocket(wsUrl);
                
                ws.onopen = function() {
                    updateConnectionStatus('connected');
                    // Request current configuration
                    ws.send('ROTATOR:GET_CONFIG');
                };
                
                ws.onmessage = function(event) {
                    console.log('Received:', event.data);
                    
                    if (event.data.startsWith('ROTATOR:')) {
                        const message = event.data.substring(8);
                        
                        if (message.startsWith('CONFIG:')) {
                            // Parse configuration: "CONFIG:mode,minAngle,maxAngle"
                            const config = message.substring(7).split(',');
                            if (config.length === 3) {
                                rotatorMode = parseInt(config[0]);
                                minAngle = parseFloat(config[1]);
                                maxAngle = parseFloat(config[2]);
                                updateModeDisplay();
                            }
                        } else {
                            // Parse angle value
                            const angle = parseFloat(message);
                            if (!isNaN(angle)) {
                                totalRotation = angle;
                                updateAngleDisplay(totalRotation);
                            }
                        }
                    }
                };
                
                ws.onclose = function() {
                    updateConnectionStatus('disconnected');
                    // Attempt to reconnect after 3 seconds
                    setTimeout(connectWebSocket, 3000);
                };
                
                ws.onerror = function(error) {
                    console.error('WebSocket error:', error);
                    updateConnectionStatus('disconnected');
                };
                
            } catch (error) {
                console.error('WebSocket connection failed:', error);
                updateConnectionStatus('disconnected');
                setTimeout(connectWebSocket, 3000);
            }
        }

        // Initialize
        updateConnectionStatus("connecting");
        updateModeDisplay();
        
        // Auto-connect on page load
        setTimeout(connectWebSocket, 500);
        
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
