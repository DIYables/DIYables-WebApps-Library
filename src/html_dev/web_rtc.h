#ifndef WEB_RTC_HTML_H
#define WEB_RTC_HTML_H

const char WEB_RTC_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web RTC - DIYables</title>
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
            margin: 0;
            padding: 0;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
        }
        
        .container {
            background: white;
            border-radius: 0;
            box-shadow: none;
            width: 100%;
            flex: 1;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px 40px 100px 40px;
            text-align: center;
            display: flex;
            flex-direction: column;
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
            align-items: center;
            width: 100%;
            padding: 20px 0;
        }
        
        .clock-display {
            background: linear-gradient(145deg, #ffffff 0%, #f8f9fa 100%);
            border-radius: 20px;
            padding: 25px;
            margin: 20px 0;
            border: 1px solid #e9ecef;
            max-width: 580px;
            width: 95%;
            box-shadow: 0 8px 25px rgba(0, 0, 0, 0.08), 
                        0 1px 6px rgba(0, 0, 0, 0.04);
            position: relative;
        }
        
        .clock-display::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            right: 0;
            height: 4px;
            background: linear-gradient(90deg, #ffecd2 0%, #fcb69f 50%, #ffecd2 100%);
            border-radius: 20px 20px 0 0;
        }
        
        .time-section {
            margin: 25px 0;
            position: relative;
        }
        
        .time-section h2 {
            color: #495057;
            font-size: 1.3em;
            margin-bottom: 15px;
            font-weight: 600;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
        }
        
        .time-section h2::before {
            content: '';
            width: 8px;
            height: 8px;
            border-radius: 50%;
            display: inline-block;
        }
        
        .time-section:first-of-type h2::before {
            background: linear-gradient(135deg, #dc3545, #ff6b6b);
            box-shadow: 0 0 10px rgba(220, 53, 69, 0.3);
        }
        
        .time-section:last-of-type h2::before {
            background: linear-gradient(135deg, #28a745, #20c997);
            box-shadow: 0 0 10px rgba(40, 167, 69, 0.3);
        }
        
        .arduino-time, .client-time {
            font-size: 1.8em;
            font-weight: 700;
            margin: 12px 0;
            padding: 20px 15px;
            border-radius: 12px;
            background: linear-gradient(145deg, #ffffff, #f8f9fa);
            border: 2px solid transparent;
            background-clip: padding-box;
            position: relative;
            transition: all 0.3s ease;
            text-align: center;
            min-height: 70px;
            display: flex;
            align-items: center;
            justify-content: center;
            word-break: break-all;
            overflow-wrap: break-word;
        }
        
        .arduino-time {
            color: #dc3545;
            border-color: rgba(220, 53, 69, 0.2);
            box-shadow: 0 4px 15px rgba(220, 53, 69, 0.1),
                        inset 0 1px 3px rgba(255, 255, 255, 0.8);
        }
        
        .arduino-time:hover {
            transform: translateY(-2px);
            box-shadow: 0 8px 25px rgba(220, 53, 69, 0.15),
                        inset 0 1px 3px rgba(255, 255, 255, 0.8);
            border-color: rgba(220, 53, 69, 0.3);
        }
        
        .client-time {
            color: #28a745;
            border-color: rgba(40, 167, 69, 0.2);
            box-shadow: 0 4px 15px rgba(40, 167, 69, 0.1),
                        inset 0 1px 3px rgba(255, 255, 255, 0.8);
        }
        
        .client-time:hover {
            transform: translateY(-2px);
            box-shadow: 0 8px 25px rgba(40, 167, 69, 0.15),
                        inset 0 1px 3px rgba(255, 255, 255, 0.8);
            border-color: rgba(40, 167, 69, 0.3);
        }
        
        .time-diff {
            font-size: 1.0em;
            color: #6c757d;
            margin-top: 25px;
            padding: 15px 20px;
            background: linear-gradient(145deg, #f8f9fa, #e9ecef);
            border-radius: 10px;
            border: 1px solid rgba(108, 117, 125, 0.2);
            font-weight: 500;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 8px;
        }
        
        .time-diff::before {
            content: '⏱️';
            font-size: 1.2em;
        }
        
        .sync-pulse {
            animation: syncPulse 2s infinite;
        }
        
        .sync-button {
            background: linear-gradient(135deg, #ff6b6b 0%, #ee5a52 100%);
            color: white;
            border: none;
            border-radius: 25px;
            padding: 14px 35px;
            font-size: 1.1em;
            font-weight: 700;
            cursor: pointer;
            transition: all 0.3s ease;
            margin: 15px 10px;
            box-shadow: 0 6px 20px rgba(255, 107, 107, 0.25),
                        0 2px 8px rgba(0, 0, 0, 0.08);
            position: relative;
            overflow: hidden;
            text-transform: uppercase;
            letter-spacing: 0.5px;
            border: 2px solid transparent;
        }
        
        .sync-button::before {
            content: '';
            position: absolute;
            top: 0;
            left: -100%;
            width: 100%;
            height: 100%;
            background: linear-gradient(90deg, transparent, rgba(255, 255, 255, 0.3), transparent);
            transition: left 0.6s;
        }
        
        .sync-button:hover {
            transform: translateY(-3px) scale(1.02);
            box-shadow: 0 12px 35px rgba(255, 107, 107, 0.4),
                        0 5px 15px rgba(0, 0, 0, 0.15);
            border-color: rgba(255, 255, 255, 0.3);
        }
        
        .sync-button:hover::before {
            left: 100%;
        }
        
        .sync-button:active {
            transform: translateY(-1px) scale(0.98);
            transition: all 0.1s ease;
        }
        
        .sync-button:disabled {
            background: linear-gradient(135deg, #6c757d, #5a6268);
            cursor: not-allowed;
            transform: none;
            box-shadow: 0 4px 15px rgba(108, 117, 125, 0.3);
            border-color: transparent;
        }
        
        .sync-button:disabled::before {
            display: none;
        }
        
        .sync-button.syncing {
            background: linear-gradient(135deg, #28a745, #20c997);
            animation: syncSuccess 0.6s ease;
        }
        
        @keyframes syncSuccess {
            0% { transform: scale(1); }
            50% { transform: scale(1.05); }
            100% { transform: scale(1); }
        }
        
        .info-panel {
            background: linear-gradient(145deg, #e3f2fd 0%, #f3e5f5 100%);
            border-radius: 12px;
            padding: 20px;
            margin: 15px 0;
            border: 1px solid rgba(33, 150, 243, 0.2);
            max-width: 580px;
            width: 95%;
            position: relative;
            box-shadow: 0 4px 15px rgba(33, 150, 243, 0.08);
            text-align: left;
        }
        
        .info-panel::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            width: 5px;
            height: 100%;
            background: linear-gradient(180deg, #2196f3, #9c27b0);
        }
        
        .info-panel h3 {
            color: #1976d2;
            margin-bottom: 15px;
            font-size: 1.3em;
            font-weight: 700;
            display: flex;
            align-items: center;
            gap: 10px;
        }
        
        .info-panel h3::before {
            content: '💡';
            font-size: 1.2em;
        }
        
        .info-panel p {
            color: #424242;
            line-height: 1.7;
            margin: 8px 0;
            padding-left: 15px;
            position: relative;
        }
        
        .info-panel p::before {
            content: '•';
            position: absolute;
            left: 0;
            color: #2196f3;
            font-weight: bold;
            font-size: 1.2em;
        }
        
        .info-panel p strong {
            color: #1976d2;
            font-weight: 600;
        }
        
        .footer {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            text-align: center;
            padding: 15px 20px;
            height: 40px;
            width: 100%;
            font-size: 0.9em;
            border-top: 1px solid rgba(255, 255, 255, 0.1);
            position: fixed;
            bottom: 0;
            left: 0;
            z-index: 1000;
            box-sizing: border-box;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        
        .footer a {
            color: #ffffff;
            text-decoration: none;
            font-weight: 500;
        }
        
        .footer a:hover {
            text-decoration: underline;
        }
        
        @media (max-width: 768px) {
            .container {
                padding: 15px 20px 80px 20px;
            }
            
            .header h1 {
                font-size: 1.8em;
            }
            
            .top-nav {
                margin: -20px -20px 0 -20px;
                padding: 10px 15px;
            }
            
            .websocket-status {
                margin: 0 -20px 15px -20px;
                padding: 8px 15px;
            }
            
            .clock-display {
                padding: 20px 15px;
                margin: 15px 0;
                width: 100%;
                max-width: none;
            }
            
            .arduino-time, .client-time {
                font-size: 1.3em;
                min-height: 60px;
                padding: 15px 10px;
                margin: 10px 0;
            }
            
            .sync-button {
                padding: 12px 25px;
                font-size: 1em;
                margin: 12px 5px;
            }
            
            .info-panel {
                padding: 15px;
                margin: 12px 0;
                width: 100%;
                max-width: none;
            }
            
            .info-panel h3 {
                font-size: 1.1em;
            }
            
            .info-panel p {
                font-size: 0.9em;
                line-height: 1.5;
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
            <a href="https://diyables.io/webapps-r4" target="_blank" class="tutorial-link">📚 Tutorial</a>
        </div>
        
        <div class="websocket-status">
            WebSocket: <span id="connectionText">Disconnected</span>
        </div>
        
        <div class="header">
            <h1>🕐 Web RTC</h1>
        </div>
        
        <div class="content">
            <div class="clock-display">
                <div class="time-section">
                    <h2>Arduino Time</h2>
                    <div id="arduinoTime" class="arduino-time">
                        --:--:-- --<br>--, -- --, ----
                    </div>
                </div>
                
                <div class="time-section">
                    <h2>Your Device Time</h2>
                    <div id="clientTime" class="client-time">
                        --:--:-- --<br>--, -- --, ----
                    </div>
                </div>
                
                <div id="timeDiff" class="time-diff">
                    Time difference: --
                </div>
            </div>
            
            <button id="syncButton" class="sync-button" disabled>
                🔄 Sync Arduino Time
            </button>
            
            <div class="info-panel">
                <h3>About Local Time Synchronization</h3>
                <p><strong>Arduino Time:</strong> Stores your actual local time directly</p>
                <p><strong>Device Time:</strong> Your browser's current local time</p>
                <p><strong>Sync Function:</strong> Sends local time components (no timezone conversion)</p>
                <p><strong>Display Match:</strong> Both web and Arduino Serial show identical time</p>
            </div>
        </div>
    </div>

    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>

    <script>
        let socket;
        let isConnected = false;
        let clientTimeInterval;
        let arduinoTimestamp = 0;
        let lastSyncTime = 0;
        
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
        
        function initWebSocket() {
            const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
            const wsUrl = `${protocol}//${window.location.hostname}:81`;
            
            socket = new WebSocket(wsUrl);
            
            socket.onopen = function(event) {
                isConnected = true;
                updateConnectionStatus('connected');
                document.getElementById('syncButton').disabled = false;
                
                // Request current Arduino time
                requestArduinoTime();
            };
            
            socket.onclose = function(event) {
                isConnected = false;
                updateConnectionStatus('disconnected');
                document.getElementById('syncButton').disabled = true;
                
                // Try to reconnect after 3 seconds
                setTimeout(initWebSocket, 3000);
            };
            
            socket.onerror = function(error) {
                console.error('WebSocket error:', error);
                updateConnectionStatus('disconnected');
            };
            
            socket.onmessage = function(event) {
                console.log('Received:', event.data);
                handleArduinoMessage(event.data);
            };
        }
        
        function handleArduinoMessage(message) {
            if (message.startsWith('TIME:')) {
                const timestamp = parseInt(message.substring(5));
                if (timestamp > 0) {
                    arduinoTimestamp = timestamp;
                    lastSyncTime = Date.now();
                    updateArduinoTime();
                }
            } else if (message.startsWith('DATETIME:')) {
                const parts = message.substring(9).split(',');
                if (parts.length >= 6) {
                    const [year, month, day, hour, minute, second] = parts.map(Number);
                    
                    // Display Arduino time exactly as received
                    displayArduinoTime(year, month, day, hour, minute, second);
                }
            }
        }
        
        function requestArduinoTime() {
            if (isConnected && socket.readyState === WebSocket.OPEN) {
                socket.send('RTC:GET_TIME');
            }
        }
        
        function syncArduinoTime() {
            if (!isConnected || socket.readyState !== WebSocket.OPEN) {
                alert('Not connected to Arduino');
                return;
            }
            
            // Get local time and adjust for timezone offset
            const now = new Date();
            const localTimestamp = Math.floor(now.getTime() / 1000);
            // Adjust for timezone offset to get true local time
            const timezoneOffset = now.getTimezoneOffset() * 60; // Convert minutes to seconds
            const adjustedTimestamp = localTimestamp - timezoneOffset;
            const message = 'RTC:SYNC:' + adjustedTimestamp;
            
            socket.send(message);
            console.log('Sent sync command with local time components:', message);
            
            // Update button feedback
            const syncBtn = document.getElementById('syncButton');
            const originalText = syncBtn.textContent;
            syncBtn.textContent = '✅ Synced!';
            syncBtn.disabled = true;
            
            setTimeout(() => {
                syncBtn.textContent = originalText;
                syncBtn.disabled = false;
            }, 2000);
            
            // Request updated time after sync
            setTimeout(requestArduinoTime, 500);
        }
        
        function updateClientTime() {
            const now = new Date();
            
            // Format time as 12:36:33 PM
            const timeOptions = { 
                hour: '2-digit', 
                minute: '2-digit', 
                second: '2-digit', 
                hour12: true 
            };
            const timeStr = now.toLocaleTimeString('en-US', timeOptions);
            
            // Format date as Thursday, August 28, 2025
            const dateOptions = { 
                weekday: 'long', 
                year: 'numeric', 
                month: 'long', 
                day: 'numeric' 
            };
            const dateStr = now.toLocaleDateString('en-US', dateOptions);
            
            // Display on two lines with HTML break
            document.getElementById('clientTime').innerHTML = `${timeStr}<br>${dateStr}`;
        }
        
        function displayArduinoTime(year, month, day, hour, minute, second) {
            // Create a Date object from Arduino time components
            const arduinoDate = new Date(year, month - 1, day, hour, minute, second);
            
            // Format exactly like device time for consistency
            const timeOptions = { 
                hour: '2-digit', 
                minute: '2-digit', 
                second: '2-digit', 
                hour12: true 
            };
            const timeStr = arduinoDate.toLocaleTimeString('en-US', timeOptions);
            
            const dateOptions = { 
                weekday: 'long', 
                year: 'numeric', 
                month: 'long', 
                day: 'numeric' 
            };
            const dateStr = arduinoDate.toLocaleDateString('en-US', dateOptions);
            
            // Display on two lines with HTML break
            document.getElementById('arduinoTime').innerHTML = `${timeStr}<br>${dateStr}`;
            
            // Calculate time difference immediately
            calculateTimeDifference(arduinoDate);
        }
        
        function calculateTimeDifference(arduinoDate) {
            // Current device time
            const now = new Date();
            
            // Calculate difference in milliseconds, then convert to seconds
            const diffMs = Math.abs(now.getTime() - arduinoDate.getTime());
            const diffSeconds = Math.floor(diffMs / 1000);
            
            let diffText;
            if (diffSeconds < 60) {
                diffText = `${diffSeconds} seconds`;
            } else {
                diffText = `${Math.floor(diffSeconds / 60)} minutes`;
            }
            document.getElementById('timeDiff').textContent = `Time difference: ${diffText}`;
        }
        
        function updateArduinoTime() {
            // This function is kept for compatibility but may not be needed
            // since we now display Arduino time directly from components
        }
        
        // Initialize everything when page loads
        window.onload = function() {
            // Update client time every second
            clientTimeInterval = setInterval(updateClientTime, 1000);
            updateClientTime();
            
            // Update Arduino time display every second
            setInterval(updateArduinoTime, 1000);
            
            // Request Arduino time every 30 seconds
            setInterval(requestArduinoTime, 30000);
            
            // Add click handler to sync button
            document.getElementById('syncButton').onclick = syncArduinoTime;
            
            // Auto-connect after 500ms like other apps
            setTimeout(initWebSocket, 500);
        };
        
        // Cleanup when page unloads
        window.onbeforeunload = function() {
            if (clientTimeInterval) {
                clearInterval(clientTimeInterval);
            }
            if (socket) {
                socket.close();
            }
        };
    </script>
</body>
</html>
)HTMLDELIM";

#endif
