#ifndef CUSTOM_PAGE_HTML_H
#define CUSTOM_PAGE_HTML_H

const char CUSTOM_PAGE_HTML[] PROGMEM = R"HTML_WRAPPER(
<!DOCTYPE html>
<html>
<head>
    <title>Custom WebApp</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        #rawMessage, #status {
            color: #007bff;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <h1>Custom WebApp</h1>
    <p>WebSocket: <span id="status">Disconnected</span></p>
    
    <input type="text" id="messageInput" placeholder="Type message to Arduino">
    <button onclick="sendMessage()">Send</button>
    <br><br>
    
    <div>Message from Arduino: <span id="rawMessage">--</span></div>
    
    <script>
        // WebSocket message identifier for this custom app
        const APP_IDENTIFIER = 'CUSTOM:';
        
        let ws = null;
        
        function connectWebSocket() {
            ws = new WebSocket('ws://' + location.hostname + ':81');
            
            ws.onopen = function() {
                document.getElementById('status').textContent = 'Connected';
            };
            
            ws.onclose = function() {
                document.getElementById('status').textContent = 'Disconnected';
                // Auto reconnect after 5 seconds
                setTimeout(connectWebSocket, 5000);
            };
            
            ws.onmessage = function(event) {
                // Only process messages that start with our app identifier
                if (event.data.startsWith(APP_IDENTIFIER)) {
                    // Remove the identifier and display the message
                    let message = event.data.substring(APP_IDENTIFIER.length);
                    document.getElementById('rawMessage').textContent = message;
                }
                // Ignore messages that don't belong to our app
            };
            
            ws.onerror = function(error) {
                document.getElementById('status').textContent = 'Error';
            };
        }
        
        function send(message) {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(APP_IDENTIFIER + message);
            }
        }
        
        function sendMessage() {
            let input = document.getElementById('messageInput');
            if (input.value && ws && ws.readyState === WebSocket.OPEN) {
                ws.send(APP_IDENTIFIER + input.value);
                input.value = '';
            }
        }
        
        // Send message when Enter is pressed
        document.getElementById('messageInput').addEventListener('keypress', function(e) {
            if (e.key === 'Enter') {
                sendMessage();
            }
        });
        
        // Start connection when page loads
        window.addEventListener('load', function() {
            connectWebSocket();
        });
        
        // Reconnect when page becomes visible
        document.addEventListener('visibilitychange', function() {
            if (!document.hidden && (!ws || ws.readyState !== WebSocket.OPEN)) {
                setTimeout(connectWebSocket, 1000);
            }
        });
    </script>
</body>
</html>
)HTML_WRAPPER";

#endif
