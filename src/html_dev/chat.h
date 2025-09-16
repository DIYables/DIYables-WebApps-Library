#ifndef CHAT_HTML_H
#define CHAT_HTML_H

const char CHAT_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Chat - DIYables WebApp</title>
    <link rel="icon" href="https://diyables.io/images/page/diyables.svg">
    <style>
        :root {
            --safe-area-inset-top: env(safe-area-inset-top);
            --safe-area-inset-bottom: env(safe-area-inset-bottom);
            --safe-area-inset-left: env(safe-area-inset-left);
                        .chat-input {
                padding: 12px;
                padding-bottom: max(20px, calc(env(safe-area-inset-bottom) + 8px));
                gap: 8px;
                position: fixed;
                bottom: 50px;
                left: 0;
                right: 0;
                background: white;
                border-top: 1px solid #dee2e6;
                z-index: 1001;
                min-height: 60px;
                box-sizing: border-box;
                box-shadow: 0 -2px 10px rgba(0,0,0,0.1);
            }inset-right: env(safe-area-inset-right);
        }
        
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            -webkit-font-smoothing: antialiased;
            -moz-osx-font-smoothing: grayscale;
        }
        
        html {
            /* Prevent elastic scrolling on mobile */
            overscroll-behavior: none;
            -webkit-overflow-scrolling: touch;
        }
        
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            background: white;
            height: 100vh;
            margin: 0;
            padding: 0 0 40px 0;
            /* Prevent pull-to-refresh on mobile */
            overscroll-behavior-y: contain;
            display: flex;
            flex-direction: column;
        }
        
        .chat-container {
            background: white;
            border-radius: 0;
            box-shadow: none;
            width: 100%;
            max-width: 1200px;
            margin: 0 auto;
            flex: 1;
            display: flex;
            flex-direction: column;
            overflow: hidden;
            position: relative;
        }
        
        .chat-header {
            background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%);
            color: white;
            padding: 20px;
            text-align: center;
            position: relative;
            flex-shrink: 0;
        }
        
        .chat-header h1 {
            font-size: 2.0em;
            margin-bottom: 5px;
        }
        
        .chat-header p {
            font-size: 1.0em;
            opacity: 0.9;
        }
        
        .status-indicator {
            position: absolute;
            top: 50%;
            right: 20px;
            transform: translateY(-50%);
            width: 12px;
            height: 12px;
            border-radius: 50%;
            background: #dc3545;
            transition: background 0.3s;
        }
        
        .status-indicator.connected {
            background: #28a745;
            box-shadow: 0 0 10px rgba(40, 167, 69, 0.5);
        }
        
        .top-nav {
            background: #f8f9fa;
            padding: 10px 20px;
            border-bottom: 1px solid #e9ecef;
            flex-shrink: 0;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .home-link {
            color: #43e97b;
            text-decoration: none;
            font-size: 1.1em;
            font-weight: bold;
            transition: all 0.3s;
            padding: 8px 12px;
            border-radius: 6px;
            background: rgba(67, 233, 123, 0.1);
        }
        
        .home-link:hover {
            background: rgba(67, 233, 123, 0.2);
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
            flex-shrink: 0;
            text-align: center;
            font-size: 0.9em;
            color: black;
        }
        
        .websocket-status #connectionStatus {
            font-weight: bold;
        }
        
        .footer {
            background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%);
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
        
        .chat-messages {
            flex: 1;
            padding: 20px;
            padding-bottom: 120px; /* Space for fixed input on mobile */
            overflow-y: auto;
            background: #f8f9fa;
            -webkit-overflow-scrolling: touch;
            overscroll-behavior: contain;
            scroll-behavior: smooth;
        }
        
        .chat-messages::-webkit-scrollbar {
            width: 6px;
        }
        
        .chat-messages::-webkit-scrollbar-track {
            background: #f1f1f1;
        }
        
        .chat-messages::-webkit-scrollbar-thumb {
            background: #ccc;
            border-radius: 3px;
        }
        
        .message {
            margin-bottom: 15px;
            animation: fadeIn 0.3s ease-in;
        }
        
        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(10px); }
            to { opacity: 1; transform: translateY(0); }
        }
        
        .message.user {
            text-align: right;
        }
        
        .message.arduino {
            text-align: left;
        }
        
        .message.system {
            text-align: center;
        }
        
        .message-bubble {
            display: inline-block;
            max-width: 80%;
            padding: 12px 16px;
            border-radius: 18px;
            word-wrap: break-word;
            position: relative;
        }
        
        .message.user .message-bubble {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
        }
        
        .message.arduino .message-bubble {
            background: #e9ecef;
            color: #333;
            border: 1px solid #dee2e6;
        }
        
        .message.system .message-bubble {
            background: #fff3cd;
            color: #856404;
            border: 1px solid #ffeaa7;
            font-size: 0.9em;
        }
        
        .message-time {
            font-size: 0.75em;
            opacity: 0.7;
            margin-top: 5px;
        }
        
        .message.user .message-time {
            text-align: right;
        }
        
        .message.arduino .message-time {
            text-align: left;
        }
        
        .message.system .message-time {
            text-align: center;
        }
        
        .chat-input {
            background: white;
            padding: 20px;
            border-top: 1px solid #dee2e6;
            display: flex;
            gap: 10px;
            align-items: center;
            flex-shrink: 0;
            position: relative;
            z-index: 10;
        }
        
        /* Desktop keeps relative positioning */
        @media (min-width: 769px) {
            .chat-input {
                position: relative;
                bottom: auto;
            }
            
            .chat-messages {
                padding-bottom: 20px; /* Normal padding for desktop */
            }
        }
        
        .message-input {
            flex: 1;
            border: 2px solid #e9ecef;
            border-radius: 25px;
            padding: 12px 20px;
            font-size: 16px;
            outline: none;
            transition: border-color 0.3s;
            -webkit-appearance: none;
            appearance: none;
            -webkit-border-radius: 25px;
            background-clip: padding-box;
        }
        
        .message-input:focus {
            border-color: #667eea;
        }
        
        /* Fix for iOS zoom */
        @supports (-webkit-touch-callout: none) {
            .message-input {
                font-size: 16px;
                transform: translateZ(0);
            }
        }
        
        .send-button {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            border: none;
            border-radius: 50%;
            width: 50px;
            height: 50px;
            display: flex;
            align-items: center;
            justify-content: center;
            cursor: pointer;
            transition: transform 0.2s, box-shadow 0.2s;
            -webkit-tap-highlight-color: transparent;
            position: relative;
            overflow: hidden;
        }
        
        .send-button:hover {
            transform: scale(1.05);
            box-shadow: 0 5px 15px rgba(102, 126, 234, 0.4);
        }
        
        .send-button:active {
            transform: scale(0.95);
        }
        
        .send-button:focus {
            outline: 2px solid #667eea;
            outline-offset: 2px;
        }
        
        .send-button:disabled {
            background: #ccc;
            cursor: not-allowed;
            transform: none;
            box-shadow: none;
        }
        
        .typing-indicator {
            display: none;
            margin-bottom: 15px;
            text-align: left;
        }
        
        .typing-bubble {
            display: inline-block;
            background: #e9ecef;
            border: 1px solid #dee2e6;
            padding: 12px 16px;
            border-radius: 18px;
            color: #666;
            font-style: italic;
        }
        
        @media (max-width: 768px) {
            body {
                margin: 0;
                padding: 0 0 90px 0;
                align-items: stretch;
            }
            
            .chat-container {
                width: 100%;
                height: calc(100vh - 90px);
                max-height: none;
                border-radius: 0;
                box-shadow: none;
            }
            
            .chat-header {
                padding: 15px 20px;
                padding-top: max(15px, env(safe-area-inset-top));
            }
            
            .footer {
                height: 50px;
                padding: 10px 15px;
                font-size: 0.8em;
            }
            
            .chat-header h1 {
                font-size: 1.3em;
                margin-bottom: 3px;
            }
            
            .chat-header p {
                font-size: 0.8em;
            }
            
            .home-nav {
                padding: 8px 15px;
            }
            
            .home-link {
                font-size: 1em;
                padding: 6px 10px;
            }
            
            .status-indicator {
                right: 15px;
                width: 10px;
                height: 10px;
            }
            
            .chat-messages {
                padding: 15px;
                padding-bottom: 110px; /* Extra space for fixed input + footer on mobile */
            }
            
            .message {
                margin-bottom: 12px;
            }
            
            .message-bubble {
                max-width: 85%;
                padding: 10px 14px;
                font-size: 0.95em;
                line-height: 1.4;
            }
            
            .typing-indicator {
                margin: 0 15px 10px;
            }
            
            .typing-bubble {
                padding: 10px 14px;
                font-size: 0.9em;
            }
            
            .chat-input {
                padding: 15px;
                padding-bottom: max(25px, calc(env(safe-area-inset-bottom) + 10px));
                gap: 12px;
                position: fixed;
                bottom: 50px;
                left: 0;
                right: 0;
                background: white;
                border-top: 1px solid #dee2e6;
                z-index: 1001;
                box-shadow: 0 -2px 10px rgba(0,0,0,0.1);
            }
            
            .message-input {
                font-size: 16px; /* Prevents zoom on iOS */
                padding: 14px 18px;
                border-radius: 22px;
                min-height: 44px; /* Better touch target */
            }
            
            .send-button {
                width: 44px;
                height: 44px;
                flex-shrink: 0;
            }
        }
        
        @media (max-width: 480px) {
            .chat-header {
                padding: 12px 15px;
                padding-top: max(12px, env(safe-area-inset-top));
            }
            
            .chat-header h1 {
                font-size: 1.2em;
            }
            
            .home-nav {
                padding: 6px 12px;
            }
            
            .home-link {
                font-size: 0.9em;
                padding: 5px 8px;
            }
            
            .status-indicator {
                right: 10px;
            }
            
            .chat-messages {
                padding: 12px;
                padding-bottom: 110px; /* Space for fixed input + footer on small screens */
            }
            
            .message-bubble {
                max-width: 88%;
                padding: 9px 13px;
                font-size: 0.9em;
            }
            
            .chat-input {
                padding: 12px;
                padding-bottom: max(20px, calc(env(safe-area-inset-bottom) + 8px));
                gap: 10px;
                position: fixed;
                bottom: 0;
                left: 0;
                right: 0;
                background: white;
                border-top: 1px solid #dee2e6;
                z-index: 100;
            }
            
            .message-input {
                padding: 12px 16px;
                border-radius: 20px;
                font-size: 16px;
            }
            
            .send-button {
                width: 40px;
                height: 40px;
            }
        }
        
        @media (max-width: 360px) {
            .chat-header h1 {
                font-size: 1.1em;
            }
            
            .chat-header p {
                font-size: 0.75em;
            }
            
            .message-bubble {
                padding: 8px 12px;
                font-size: 0.85em;
            }
        }
    </style>
</head>
<body>
    <div class="chat-container">
        <div class="top-nav">
            <a href="/" class="home-link">🏠 Home</a>
            <a href="https://diyables.io/webapps-r4" class="tutorial-link" target="_blank">📚 Tutorial</a>
        </div>
        <div class="websocket-status" id="websocketStatus">
            WebSocket: <span id="connectionStatus">Disconnected</span>
        </div>
        <div class="chat-header">
            <h1>💬 Arduino Chat</h1>
            <p>Chat with your Arduino via WebSocket</p>
        </div>
        
        <div class="chat-messages" id="chatMessages">
            <div class="message system">
                <div class="message-bubble">
                    Welcome to Arduino Chat! Start a conversation with your Arduino board.
                </div>
                <div class="message-time" id="welcomeTime"></div>
            </div>
        </div>
        
        <div class="typing-indicator" id="typingIndicator">
            <div class="typing-bubble">Arduino is thinking...</div>
        </div>
        
        <div class="chat-input">
            <input type="text" class="message-input" id="messageInput" 
                   placeholder="Type your message..." 
                   onkeypress="handleKeyPress(event)">
            <button class="send-button" id="sendButton" onclick="sendMessage()" disabled>
                <svg width="24" height="24" viewBox="0 0 24 24" fill="currentColor">
                    <path d="M2,21L23,12L2,3V10L17,12L2,14V21Z"/>
                </svg>
            </button>
        </div>
    </div>
    
    <script>
        let ws = null;
        let isConnected = false;
        
        const chatMessages = document.getElementById('chatMessages');
        const messageInput = document.getElementById('messageInput');
        const sendButton = document.getElementById('sendButton');
        const typingIndicator = document.getElementById('typingIndicator');
        const welcomeTime = document.getElementById('welcomeTime');
        
        // Set welcome message time
        welcomeTime.textContent = new Date().toLocaleTimeString();
        
        function connect() {
            if (ws && ws.readyState === WebSocket.OPEN) {
                return;
            }
            
            const wsUrl = 'ws://' + window.location.hostname + ':81';
            addSystemMessage('Connecting to ' + window.location.hostname + '...');
            
            ws = new WebSocket(wsUrl);
            
            ws.onopen = function() {
                isConnected = true;
                updateConnectionStatus('connected');
                addSystemMessage('Connected to Arduino! You can now start chatting.');
                sendButton.disabled = false;
            };
            
            ws.onmessage = function(event) {
                hideTypingIndicator();
                addArduinoMessage(event.data);
                console.log('Received from Arduino:', event.data);
            };
            
            ws.onclose = function() {
                isConnected = false;
                updateConnectionStatus('disconnected');
                addSystemMessage('Connection lost. Attempting to reconnect...');
                sendButton.disabled = true;
                
                // Auto-reconnect after 3 seconds
                setTimeout(connect, 3000);
            };
            
            ws.onerror = function(error) {
                hideTypingIndicator();
                addSystemMessage('Connection error occurred');
                console.error('WebSocket error:', error);
            };
        }
        
        function updateConnectionStatus(status) {
            const connectionText = document.getElementById('connectionStatus');
            connectionText.textContent = status;
            console.log('WebSocket ' + status);
            
            if(status == 'connected')
                connectionText.style.color = '#007bff';
            else if(status == 'connecting')
                connectionText.style.color = '#6c757d';
            else
                connectionText.style.color = '#dc3545';
        }
        
        function addMessage(content, sender, time) {
            const messageDiv = document.createElement('div');
            messageDiv.className = 'message ' + sender;
            
            const timeStr = time || new Date().toLocaleTimeString();
            
            messageDiv.innerHTML = 
                '<div class="message-bubble">' + content + '</div>' +
                '<div class="message-time">' + timeStr + '</div>';
            
            chatMessages.appendChild(messageDiv);
            
            // Use smooth scrolling function
            setTimeout(() => {
                if (typeof scrollToBottom === 'function') {
                    scrollToBottom();
                } else {
                    chatMessages.scrollTop = chatMessages.scrollHeight;
                }
            }, 50);
        }
        
        function addUserMessage(content) {
            addMessage(content, 'user');
        }
        
        function addArduinoMessage(content) {
            addMessage(content, 'arduino');
        }
        
        function addSystemMessage(content) {
            addMessage(content, 'system');
        }
        
        function showTypingIndicator() {
            typingIndicator.style.display = 'block';
            setTimeout(() => {
                if (typeof scrollToBottom === 'function') {
                    scrollToBottom();
                } else {
                    chatMessages.scrollTop = chatMessages.scrollHeight;
                }
            }, 50);
        }
        
        function hideTypingIndicator() {
            typingIndicator.style.display = 'none';
        }
        
        function sendMessage() {
            const message = messageInput.value.trim();
            if (message && ws && ws.readyState === WebSocket.OPEN) {
                addUserMessage(message);
                ws.send("CHAT:" + message);
                console.log('Sent to Arduino:', message);
                messageInput.value = "";
                showTypingIndicator();
                
                // Hide typing indicator after 5 seconds if no response
                setTimeout(hideTypingIndicator, 5000);
            }
        }
        
        function handleKeyPress(event) {
            if (event.key === 'Enter') {
                sendMessage();
            }
        }
        
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
        
        // Enable send button when input has content
        messageInput.addEventListener('input', function() {
            sendButton.disabled = !messageInput.value.trim() || !isConnected;
        });
        
        // Mobile-specific enhancements
        function isMobile() {
            return window.innerWidth <= 768 || /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);
        }
        
        // Prevent zoom on input focus (iOS)
        if (isMobile()) {
            messageInput.addEventListener('touchstart', function() {
                document.querySelector('meta[name=viewport]').setAttribute('content', 
                    'width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no');
            });
            
            messageInput.addEventListener('blur', function() {
                document.querySelector('meta[name=viewport]').setAttribute('content', 
                    'width=device-width, initial-scale=1.0');
            });
        }
        
        // Smooth scrolling for mobile
        function scrollToBottom() {
            if (isMobile()) {
                chatMessages.scrollTo({
                    top: chatMessages.scrollHeight,
                    behavior: 'smooth'
                });
            } else {
                chatMessages.scrollTop = chatMessages.scrollHeight;
            }
        }
        
        // Handle keyboard show/hide on mobile
        if (isMobile()) {
            let initialViewportHeight = window.visualViewport ? window.visualViewport.height : window.innerHeight;
            
            function handleViewportChange() {
                if (window.visualViewport) {
                    const currentHeight = window.visualViewport.height;
                    const heightDifference = initialViewportHeight - currentHeight;
                    
                    if (heightDifference > 150) { // Keyboard is likely open
                        document.body.style.height = currentHeight + 'px';
                        setTimeout(scrollToBottom, 100);
                    } else { // Keyboard is likely closed
                        document.body.style.height = '100vh';
                    }
                }
            }
            
            if (window.visualViewport) {
                window.visualViewport.addEventListener('resize', handleViewportChange);
            }
            
            // Fallback for older browsers
            window.addEventListener('resize', function() {
                setTimeout(scrollToBottom, 100);
            });
        }
        
        // Touch gesture enhancements
        if (isMobile()) {
            let startY = 0;
            let scrollStart = 0;
            
            chatMessages.addEventListener('touchstart', function(e) {
                startY = e.touches[0].clientY;
                scrollStart = chatMessages.scrollTop;
            }, { passive: true });
        }
    </script>
    
    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>
</body>
</html>
)HTMLDELIM";

#endif
