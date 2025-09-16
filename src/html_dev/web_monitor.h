#ifndef WEB_MONITOR_HTML_H
#define WEB_MONITOR_HTML_H

const char WEB_MONITOR_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Monitor - DIYables WebApp</title>
    <link rel="icon" href="https://diyables.io/images/page/diyables.svg">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Consolas', 'Monaco', 'Courier New', monospace;
            background: #1e1e1e;
            color: #d4d4d4;
            height: 100vh;
            display: flex;
            flex-direction: column;
            margin: 0;
            padding: 0 0 40px 0;
        }
        
        .top-nav {
            background: #f8f9fa;
            padding: 10px 20px;
            border-bottom: 1px solid #3e3e42;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .home-link {
            color: #00d4ff !important;
            text-decoration: none;
            font-size: 1.1em;
            font-weight: bold;
            transition: all 0.3s;
            padding: 8px 12px;
            border-radius: 6px;
            background: rgba(0, 212, 255, 0.1);
        }
        
        .home-link:hover {
            background: rgba(0, 212, 255, 0.2);
            transform: scale(1.05);
            color: #00d4ff !important;
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
            background: #2d2d30;
            padding: 5px 20px;
            border-bottom: 1px solid #3e3e42;
            text-align: center;
            font-size: 0.9em;
            color: #d4d4d4;
        }
        
        .websocket-status #connectionText {
            font-weight: bold;
        }
        
        .footer {
            background: #2d2d30;
            color: #d4d4d4;
            text-align: center;
            padding: 15px 20px;
            width: 100%;
            font-size: 0.9em;
            border-top: 1px solid #3e3e42;
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
            color: #4fc1ff;
            text-decoration: none;
            font-weight: bold;
            transition: all 0.3s ease;
        }
        
        .footer a:hover {
            color: #0e639c;
            text-decoration: underline;
        }
        
        .header {
            background: #2d2d30;
            padding: 15px 20px;
            border-bottom: 1px solid #3e3e42;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .header h1 {
            font-size: 2.0em;
            color: #4fc1ff;
            margin-bottom: 5px;
        }
        
        .header p {
            font-size: 1.0em;
            opacity: 0.9;
            color: #d4d4d4;
        }
        
        .controls {
            display: flex;
            gap: 10px;
            align-items: center;
        }
        
        .btn {
            background: #0e639c;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            cursor: pointer;
            font-size: 0.9em;
            transition: background 0.3s;
        }
        
        .btn:hover {
            background: #1177bb;
        }
        
        .btn.clear {
            background: #dc3545;
        }
        
        .btn.clear:hover {
            background: #c82333;
        }
        
        .status {
            padding: 5px 10px;
            border-radius: 4px;
            font-size: 0.8em;
            font-weight: bold;
        }
        
        .status.connected {
            background: #28a745;
            color: white;
        }
        
        .status.disconnected {
            background: #dc3545;
            color: white;
        }
        
        .main-content {
            flex: 1;
            display: flex;
            flex-direction: column;
            overflow: hidden;
        }
        
        .monitor-area {
            flex: 1;
            background: #1e1e1e;
            border: 1px solid #3e3e42;
            margin: 10px;
            border-radius: 4px;
            overflow: hidden;
            display: flex;
            flex-direction: column;
        }
        
        .output {
            flex: 1;
            padding: 15px;
            overflow-y: auto;
            font-size: 14px;
            line-height: 1.4;
            white-space: pre-wrap;
            word-wrap: break-word;
        }
        
        .output::-webkit-scrollbar {
            width: 8px;
        }
        
        .output::-webkit-scrollbar-track {
            background: #2d2d30;
        }
        
        .output::-webkit-scrollbar-thumb {
            background: #555;
            border-radius: 4px;
        }
        
        .output::-webkit-scrollbar-thumb:hover {
            background: #777;
        }
        
        .message {
            margin-bottom: 5px;
            padding: 2px 0;
        }
        
        .message.info {
            color: #4fc1ff;
        }
        
        .message.warning {
            color: #ffc107;
        }
        
        .message.error {
            color: #dc3545;
        }
        
        .message.success {
            color: #28a745;
        }
        
        .timestamp {
            color: #6a6a6a;
            font-size: 0.85em;
            margin-right: 8px;
        }
        
        .input-area {
            border-top: 1px solid #3e3e42;
            padding: 15px;
            background: #252526;
            display: flex;
            gap: 10px;
        }
        
        .input-field {
            flex: 1;
            background: #3c3c3c;
            border: 1px solid #555;
            border-radius: 4px;
            padding: 10px;
            color: #d4d4d4;
            font-family: inherit;
            font-size: 14px;
        }
        
        .input-field:focus {
            outline: none;
            border-color: #0e639c;
        }
        
        .send-btn {
            background: #28a745;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 4px;
            cursor: pointer;
            font-size: 14px;
            transition: background 0.3s;
        }
        
        .send-btn:hover {
            background: #218838;
        }
        
        .send-btn:disabled {
            background: #555;
            cursor: not-allowed;
        }
        
        .stats {
            font-size: 0.8em;
            color: #6a6a6a;
        }
        
        .home-link {
            color: white;
            text-decoration: none;
            font-size: 1.1em;
            opacity: 0.9;
            transition: all 0.3s;
            background: rgba(255, 255, 255, 0.2);
            padding: 8px 12px;
            border-radius: 8px;
            font-weight: bold;
            margin-top: 5px;
            display: inline-block;
        }
        
        .home-link:hover {
            opacity: 1;
            background: rgba(255, 255, 255, 0.3);
            transform: scale(1.05);
        }
        
        @media (max-width: 768px) {
            body {
                padding-bottom: 50px;
            }
            
            .header {
                flex-direction: column;
                gap: 10px;
                align-items: stretch;
            }
            
            .home-link {
                font-size: 1em;
                padding: 6px 10px;
                border-radius: 6px;
                background: rgba(255,255,255,0.2);
            }
            
            .footer {
                height: 50px;
                padding: 10px 15px;
                font-size: 0.8em;
            }
            
            .controls {
                justify-content: center;
            }
            
            .input-area {
                flex-direction: column;
            }
        }
    </style>
</head>
<body>
    <div class="top-nav">
        <a href="/" class="home-link">🏠 Home</a>
        <a href="https://diyables.io/webapps-r4" class="tutorial-link" target="_blank">📚 Tutorial</a>
    </div>
    <div class="websocket-status" id="websocketStatus">
        WebSocket: <span id="connectionText">Disconnected</span>
    </div>
    <div class="header">
        <div>
            <h1>📊 Web Monitor</h1>
            <p>Monitor and send messages to your Arduino</p>
        </div>
        <div class="controls">
            <span class="stats">Messages: <span id="messageCount">0</span></span>
            <button class="btn clear" onclick="clearOutput()">Clear</button>
        </div>
    </div>
    
    <div class="main-content">
        <div class="monitor-area">
            <div id="output" class="output"></div>
            <div class="input-area">
                <input type="text" id="messageInput" class="input-field" 
                       placeholder="Type a message to send to Arduino..." 
                       onkeypress="handleKeyPress(event)">
                <button id="sendBtn" class="send-btn" onclick="sendMessage()" disabled>Send</button>
            </div>
        </div>
    </div>
    
    <script>
        let ws = null;
        let messageCount = 0;
        let isConnected = false;
        
        const output = document.getElementById('output');
        const messageInput = document.getElementById('messageInput');
        const sendBtn = document.getElementById('sendBtn');
        const connectionText = document.getElementById('connectionText');
        const websocketStatus = document.getElementById('websocketStatus');
        const messageCountDisplay = document.getElementById('messageCount');
        
        // Debug: Check if functions are defined
        console.log('Web Monitor script loaded');
        
        function connect() {
            console.log('Connect function called');
            if (ws && (ws.readyState === WebSocket.OPEN || ws.readyState === WebSocket.CONNECTING)) {
                return;
            }
            
            const wsUrl = 'ws://' + window.location.hostname + ':81';
            addMessage('Connecting to ' + window.location.hostname + '...', 'info');
            
            ws = new WebSocket(wsUrl);
            
            ws.onopen = function() {
                isConnected = true;
                updateConnectionStatus('connected');
                addMessage('Connected to Arduino Web Monitor!', 'success');
                sendBtn.disabled = false;
            };
            
            ws.onmessage = function(event) {
                addMessage(event.data, 'info');
                console.log('Received from Arduino:', event.data);
            };
            
            ws.onclose = function(event) {
                isConnected = false;
                updateConnectionStatus('disconnected');
                addMessage('Disconnected from Arduino', 'warning');
                sendBtn.disabled = true;
                
                // Only auto-reconnect if it wasn't a clean close
                if (event.code !== 1000) {
                    setTimeout(connect, 5000);
                }
            };
            
            ws.onerror = function(error) {
                addMessage('WebSocket error occurred', 'error');
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
        
        function addMessage(message, type) {
            if (!type) type = "";
            const timestamp = new Date().toLocaleTimeString();
            const messageElement = document.createElement('div');
            messageElement.className = 'message ' + type;
            messageElement.innerHTML = '<span class="timestamp">[' + timestamp + ']</span>' + message;
            
            output.appendChild(messageElement);
            output.scrollTop = output.scrollHeight;
            
            messageCount++;
            messageCountDisplay.textContent = messageCount;
        }
        
        function sendMessage() {
            const message = messageInput.value.trim();
            if (message && ws && ws.readyState === WebSocket.OPEN) {
                ws.send("MONITOR:" + message);
                addMessage('> ' + message, "");
                messageInput.value = "";
                console.log('Sent to Arduino:', message);
            }
        }
        
        function handleKeyPress(event) {
            if (event.key === 'Enter') {
                sendMessage();
            }
        }
        
        function clearOutput() {
            console.log('Clear output function called');
            output.innerHTML = "";
            messageCount = 0;
            messageCountDisplay.textContent = messageCount;
            addMessage('Output cleared', 'info');
        }
        
        // Auto-connect on page load and make functions globally available
        window.addEventListener('load', function() {
            // Make connect function globally available
            window.connect = connect;
            window.clearOutput = clearOutput;
            console.log('Functions made global:', typeof window.connect, typeof window.clearOutput);
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
