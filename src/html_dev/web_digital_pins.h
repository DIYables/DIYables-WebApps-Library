#ifndef WEB_DIGITAL_PINS_H
#define WEB_DIGITAL_PINS_H

const char WEB_DIGITAL_PINS_HTML[] PROGMEM = R"RAWSTRING(
<!DOCTYPE html>
<html>
<head>
<title>Digital Pins Control & Monitor - DIYables WebApp</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<link rel="icon" href="https://diyables.io/images/page/diyables.svg">
<style>
/* CSS styling will be added here */
body {
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
    background: white;
    margin: 0;
    padding: 0 0 40px 0;
    min-height: 100vh;
    display: flex;
    flex-direction: column;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
    flex: 1;
    display: flex;
    flex-direction: column;
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
        }.header {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 25px;
    text-align: center;
    border-radius: 0;
    margin-bottom: 20px;
}

.header h1 {
    font-size: 2.0em;
    margin-bottom: 5px;
}

.header p {
    font-size: 1.0em;
    opacity: 0.9;
}

.pin-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 15px;
    margin: 20px 0;
}

.pin-card {
    background: #f8f9fa;
    border: 2px solid #e9ecef;
    border-radius: 15px;
    padding: 20px;
    text-align: center;
    transition: all 0.3s ease;
}

.pin-card:hover {
    border-color: #667eea;
    box-shadow: 0 5px 15px rgba(102, 126, 234, 0.1);
}

.pin-card.active {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    border-color: #667eea;
}

.pin-card.output {
    border-color: #28a745;
}

.pin-card.input {
    border-color: #007bff;
}

.pin-label {
    font-size: 1.1em;
    font-weight: bold;
    margin-bottom: 15px;
    color: inherit;
}

.pin-state {
    font-weight: bold;
    font-size: 1.2em;
    margin: 10px 0;
}

.pin-state.on {
    color: #28a745;
}

.pin-state.off {
    color: #dc3545;
}

.pin-buttons {
    display: flex;
    gap: 10px;
    justify-content: center;
    margin-top: 10px;
}

.pin-btn {
    flex: 1;
    padding: 10px 15px;
    border: none;
    border-radius: 8px;
    font-size: 0.9em;
    font-weight: bold;
    cursor: pointer;
    transition: all 0.2s;
}

.pin-btn.on {
    background: #28a745;
    color: white;
}

.pin-btn.on:hover {
    background: #218838;
    transform: translateY(-1px);
}

.pin-btn.off {
    background: #dc3545;
    color: white;
}

.pin-btn.off:hover {
    background: #c82333;
    transform: translateY(-1px);
}

.pin-btn:disabled {
    background: #6c757d;
    cursor: not-allowed;
    transform: none;
}

.bulk-controls {
    background: #e9ecef;
    border-radius: 15px;
    padding: 20px;
    text-align: center;
    margin: 20px 0;
}

.bulk-buttons {
    display: flex;
    gap: 15px;
    justify-content: center;
    flex-wrap: wrap;
}

.bulk-button {
    padding: 12px 24px;
    border: none;
    border-radius: 25px;
    font-size: 1em;
    font-weight: bold;
    cursor: pointer;
    transition: all 0.3s;
    min-width: 120px;
    margin: 5px;
}

.bulk-button:nth-child(1) {
    background: linear-gradient(135deg, #28a745 0%, #20c997 100%);
    color: white;
}

.bulk-button:nth-child(2) {
    background: linear-gradient(135deg, #dc3545 0%, #fd7e14 100%);
    color: white;
}

.bulk-button:nth-child(3) {
    background: linear-gradient(135deg, #6f42c1 0%, #e83e8c 100%);
    color: white;
}

.bulk-button:hover {
    transform: translateY(-2px);
    box-shadow: 0 5px 15px rgba(0,0,0,0.2);
}

@media (max-width: 768px) {
    body {
        padding-bottom: 50px;
    }
      
    .container {
        padding: 20px 20px 30px 20px;
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
        WebSocket: <span id="connectionStatus">Disconnected</span>
    </div>
    <div class="header">
        <h1>📟 Digital Pins Control & Monitor</h1>
        <p>Control output pins and monitor input pins</p>
    </div>
    
    <div style="flex: 1;">
        <div class="bulk-controls">
            <h3>Bulk Controls (Output Pins Only)</h3>
            <div class="bulk-buttons">
                <button class="bulk-button" onclick="sendBulkCommand('ALL_ON')">All ON</button>
                <button class="bulk-button" onclick="sendBulkCommand('ALL_OFF')">All OFF</button>
                <button class="bulk-button" onclick="sendBulkCommand('TOGGLE_ALL')">Toggle All</button>
            </div>
        </div>
        
        <div id="pinContainer" class="pin-grid">
            <!-- Pin cards will be dynamically generated here -->
        </div>
    </div>
</div>

<script>
var ws;
var pins = {};

function applyPinStateStyle(element, state) {
    // Base pin-state styling
    element.style.fontWeight = 'bold';
    element.style.fontSize = '1.2em';
    element.style.margin = '10px 0';
    
    // State-specific styling
    if (state === 'on') {
        element.style.color = '#28a745';
    } else {
        element.style.color = '#dc3545';
    }
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

function connectWebSocket() {
    var protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    var wsUrl = protocol + '//' + window.location.host + ':81';
    
    ws = new WebSocket(wsUrl);
    
    ws.onopen = function() {
        updateConnectionStatus('connected');
        
        // Request pin configuration
        ws.send('DIGITAL_PINS:GET_PIN_CONFIG');
        // Request current pin states
        ws.send('DIGITAL_PINS:GET_PIN_STATES');
        console.log("Sent: Pin configuration and state requests");
    };
    
    ws.onclose = function() {
        updateConnectionStatus('disconnected');
        
        // Auto-reconnect after 3 seconds
        setTimeout(connectWebSocket, 3000);
    };
    
    ws.onmessage = function(event) {
        console.log("Received:", event.data);
        handleMessage(event.data);
    };
}

function handleMessage(message) {
    if (message.startsWith('PIN_CONFIG:')) {
        var config = JSON.parse(message.substring(11));
        updatePinConfiguration(config);
    } else if (message.startsWith('PIN_STATES:')) {
        var states = JSON.parse(message.substring(11));
        updatePinStates(states);
    } else if (message.startsWith('PIN_UPDATE:')) {
        var update = JSON.parse(message.substring(11));
        updateSinglePin(update.pin, update.state);
    }
}

function updatePinConfiguration(config) {
    pins = {};
    var container = document.getElementById('pinContainer');
    container.innerHTML = '';
    
    config.pins.forEach(function(pinConfig) {
        pins[pinConfig.pin] = {
            mode: pinConfig.mode,
            state: 'OFF'
        };
        
        var card = createPinCard(pinConfig.pin, pinConfig.mode);
        container.appendChild(card);
    });
}

function createPinCard(pinNumber, mode) {
    var card = document.createElement('div');
    card.id = 'pin-' + pinNumber;
    
    var title = document.createElement('h4');
    title.className = 'pin-label';
    title.textContent = 'Pin ' + pinNumber + ' (' + mode + ')';
    card.appendChild(title);
    
    if (mode === 'OUTPUT') {
        // Simple state display
        card.className = 'pin-card output';
        var stateDisplay = document.createElement('div');
        stateDisplay.className = 'pin-state off';
        stateDisplay.textContent = 'OFF';
        stateDisplay.id = 'state-' + pinNumber;
        card.appendChild(stateDisplay);
        
        // Simple control buttons
        var buttonsContainer = document.createElement('div');
        buttonsContainer.className = 'pin-buttons';
        
        var onButton = document.createElement('button');
        onButton.className = 'pin-btn on';
        onButton.textContent = 'ON';
        onButton.id = 'on-' + pinNumber;
        onButton.onclick = function() { controlPin(pinNumber, true); };
        onButton.disabled = true;
        
        var offButton = document.createElement('button');
        offButton.className = 'pin-btn off';
        offButton.textContent = 'OFF';
        offButton.id = 'off-' + pinNumber;
        offButton.onclick = function() { controlPin(pinNumber, false); };
        offButton.disabled = true;
        
        buttonsContainer.appendChild(onButton);
        buttonsContainer.appendChild(offButton);
        card.appendChild(buttonsContainer);
    } else {
        // Simple status for input pins
        card.className = 'pin-card input';
        var status = document.createElement('div');
        status.className = 'pin-state off';
        status.textContent = 'OFF';
        status.id = 'state-' + pinNumber;
        card.appendChild(status);
    }
    
    return card;
}

function updatePinStates(states) {
    for (var pin in states) {
        updateSinglePin(parseInt(pin), states[pin]);
    }
}

function updateSinglePin(pinNumber, state) {
    if (!pins[pinNumber]) return;
    
    pins[pinNumber].state = state;
    
    var stateDisplay = document.getElementById('state-' + pinNumber);
    if (stateDisplay) {
        stateDisplay.textContent = state;
        stateDisplay.className = 'pin-state ' + state.toLowerCase();
    }
    
    // Update entire pin card background when state is ON
    var pinCard = document.getElementById('pin-' + pinNumber);
    if (pinCard) {
        if (state === 'ON') {
            pinCard.classList.add('active');
        } else {
            pinCard.classList.remove('active');
        }
    }
    
    if (pins[pinNumber].mode === 'OUTPUT') {
        // Enable control buttons when connected
        var onButton = document.getElementById('on-' + pinNumber);
        var offButton = document.getElementById('off-' + pinNumber);
        
        if (onButton && offButton) {
            onButton.disabled = false;
            offButton.disabled = false;
        }
    }
}

function controlPin(pinNumber, state) {
    if (ws && ws.readyState === WebSocket.OPEN) {
        var command = 'DIGITAL_PINS:PIN_' + pinNumber + '_' + (state ? 'ON' : 'OFF');
        ws.send(command);
        console.log('Sent:', command);
        
        // Optimistically update UI
        updateSinglePin(pinNumber, state ? 'ON' : 'OFF');
    }
}

function sendBulkCommand(command) {
    var message = 'DIGITAL_PINS:' + command;
    ws.send(message);
    console.log("Sent:", message);
}

// Auto-connect on page load
window.addEventListener('load', function() {
    setTimeout(connectWebSocket, 500);
});
</script>

<div class="footer">
    Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a>
</div>
</body>
</html>
)RAWSTRING";

#endif
