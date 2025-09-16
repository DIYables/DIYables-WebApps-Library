#ifndef WEB_JOYSTICK_H
#define WEB_JOYSTICK_H

const char web_joystick_html[] PROGMEM = R"RAWSTRING(
<!DOCTYPE html>
<html>
<head>
<title>Web Joystick Control - DIYables WebApp</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
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
    min-height: 100vh;
    padding: 0 0 40px 0;
    margin: 0;
    display: flex;
    flex-direction: column;
}

.container {
    width: 100%;
    flex: 1;
    margin: 0 auto;
    max-width: 1200px;
    background: white;
    border-radius: 0;
    box-shadow: none;
    display: flex;
    flex-direction: column;
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
}.status-panel {
    position: absolute;
    top: 50%;
    right: 25px;
    transform: translateY(-50%);
    text-align: right;
}

.connection-status {
    padding: 8px 16px;
    border-radius: 20px;
    font-size: 0.9em;
    font-weight: bold;
    margin-bottom: 5px;
}

.content {
    padding: 30px;
}

.joystick-section {
    text-align: center;
    margin-bottom: 30px;
}

.joystick-container {
    background: #f8f9fa;
    border: 2px solid #e9ecef;
    border-radius: 15px;
    padding: 30px;
    margin-bottom: 20px;
    display: inline-block;
}

.joystick-canvas {
    border-radius: 10px;
    box-shadow: 0 5px 15px rgba(0,0,0,0.1);
}

.controls-panel {
    background: #f8f9fa;
    border: 2px solid #e9ecef;
    border-radius: 15px;
    padding: 20px;
    margin-bottom: 20px;
}

.controls-grid {
    display: flex;
    flex-direction: row;
    gap: 8px;
    margin-bottom: 8px;
    justify-content: center;
}

.control-item {
    background: white;
    border: 1px solid #e9ecef;
    border-radius: 6px;
    padding: 4px 8px;
    text-align: center;
}

.coordinate-display {
    font-size: 0.95em;
    font-weight: 500;
    color: #FF0000;
    padding: 2px 8px;
}

.coordinate-label {
    font-size: 0.9em;
    color: #666;
    margin-bottom: 5px;
}

.button {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    border: none;
    padding: 12px 24px;
    border-radius: 10px;
    font-size: 1em;
    font-weight: bold;
    cursor: pointer;
    transition: all 0.3s ease;
    margin: 5px;
}

.button:hover {
    transform: translateY(-2px);
    box-shadow: 0 5px 15px rgba(102, 126, 234, 0.4);
}

.button:active {
    transform: translateY(0);
}

.checkbox-container {
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 15px 0;
    font-size: 1.1em;
    color: #333;
}

.checkbox-container input[type=checkbox] {
    width: 20px;
    height: 20px;
    margin-right: 10px;
    cursor: pointer;
}

.info-panel {
    background: linear-gradient(135deg, rgba(102, 126, 234, 0.1) 0%, rgba(118, 75, 162, 0.1) 100%);
    border: 1px solid rgba(102, 126, 234, 0.2);
    border-radius: 15px;
    padding: 20px;
    margin-bottom: 20px;
}

.info-panel h3 {
    color: #667eea;
    margin-bottom: 10px;
}

.info-panel p {
    color: #666;
    line-height: 1.5;
}

.navigation {
    background: #f8f9fa;
    padding: 20px;
    border-top: 1px solid #e9ecef;
    text-align: center;
}

.nav-button {
    background: white;
    color: #667eea;
    border: 2px solid #667eea;
    text-decoration: none;
    padding: 10px 20px;
    border-radius: 10px;
    font-weight: bold;
    margin: 5px;
    display: inline-block;
    transition: all 0.3s ease;
}

.nav-button:hover {
    background: #667eea;
    color: white;
    transform: translateY(-2px);
}

/* Responsive Design */
@media (max-width: 768px) {
    body {
        padding-bottom: 50px;
    }
    
    .header {
        padding: 20px 15px;
    }
    
    .header h1 {
        font-size: 1.5em;
    }
    
    .status-panel {
        position: static;
        transform: none;
        text-align: center;
        margin-top: 15px;
    }
    
    .footer {
        height: 50px;
        padding: 10px 15px;
        font-size: 0.8em;
    }
    
    .content {
        padding: 20px 15px;
    }
    
    .controls-grid {
        grid-template-columns: 1fr;
    }
    
    .joystick-container {
        padding: 20px;
    }
    
    .navigation {
        padding: 15px;
    }
    
    .nav-button {
        display: block;
        margin: 10px auto;
        width: 90%;
        max-width: 300px;
    }
}

@media (max-width: 480px) {
    .header h1 {
        font-size: 1.3em;
    }
    
    .header p {
        font-size: 1em;
    }
}

#joystick {
    border-radius: 50%;
    box-shadow: 0 10px 30px rgba(0,0,0,0.4);
    margin: 20px auto;
    display: block;
}

.controls {
    display: flex;
    justify-content: center;
    align-items: center;
    gap: 20px;
    flex-wrap: wrap;
    margin: 20px 0;
}

button { 
    font-weight: bold; 
    font-size: 1.2em;
    padding: 12px 24px;
    border: none;
    border-radius: 25px;
    background: linear-gradient(45deg, #ff6b6b, #ee5a24);
    color: white;
    cursor: pointer;
    transition: all 0.3s ease;
    box-shadow: 0 4px 15px rgba(0,0,0,0.2);
}

button:hover {
    transform: translateY(-2px);
    box-shadow: 0 6px 20px rgba(0,0,0,0.3);
}

button:active {
    transform: translateY(0);
}

.status {
    background: rgba(255,255,255,0.2);
    border-radius: 15px;
    padding: 15px;
    margin: 20px 0;
    backdrop-filter: blur(5px);
}

.coordinates {
    display: flex;
    justify-content: center;
    gap: 30px;
    margin: 20px 0;
    flex-wrap: wrap;
}

.coordinate-box {
    background: rgba(255,255,255,0.2);
    border-radius: 10px;
    padding: 15px 25px;
    backdrop-filter: blur(5px);
    min-width: 80px;
}

.coordinate-label {
    font-size: 0.9em;
    opacity: 0.8;
    margin-bottom: 5px;
}

.coordinate-value {
    font-size: 2em;
    font-weight: bold;
    color: #ffd700;
}

.navigation {
    margin-top: 30px;
}

.nav-button {
    background: linear-gradient(45deg, #4ecdc4, #44a08d);
    margin: 0 10px;
    text-decoration: none;
    display: inline-block;
}

.nav-button:hover {
    background: linear-gradient(45deg, #44a08d, #4ecdc4);
}

/* Mobile responsive */
@media (max-width: 768px) {
    h1 {
        font-size: 2em;
    }
    
    .coordinates {
        gap: 15px;
    }
    
    .coordinate-box {
        padding: 10px 15px;
        min-width: 60px;
    }
    
    .coordinate-value {
        font-size: 1.5em;
    }
    
    button {
        font-size: 1em;
        padding: 10px 20px;
    }
}

/* Tablet responsive */
@media (min-width: 769px) and (max-width: 1023px) {
    .container {
        padding: 15px;
    }
    
    h1 {
        font-size: 2.2em;
    }
}

/* Desktop responsive */
@media (min-width: 1024px) {
    .container {
        padding: 25px;
    }
    
    h1 {
        font-size: 3em;
    }
    
    .joystick-container {
        padding: 40px;
    }
}
</style>
<script>
var canvas_width = 400, canvas_height = 400;
var radius_base = 120;
var radius_handle = 50;
var radius_shaft = 80;
var range = canvas_width/2 - 10;
var step = 12;

// Store original dimensions to prevent cumulative scaling
var original_canvas_width = 400, original_canvas_height = 400;
var original_radius_base = 120;
var original_radius_handle = 50;
var original_radius_shaft = 80;
var original_range = original_canvas_width/2 - 10;
var original_step = 12;

var ws;
var joystick = {x:0, y:0};
var click_state = 0;
var ratio = 1;
var lastSentTime = 0;
var sendInterval = 50; // Send every 50ms to prevent flooding
var lastResizeTime = 0;
var isReconnecting = false;
var joystickConfig = {
    autoReturn: false,
    sensitivity: 1.0
};
var lastSentValues = {x: 0, y: 0}; // Track last sent values for sensitivity threshold

function init() {
    var width = window.innerWidth;
    var height = window.innerHeight;

    // Responsive sizing - always calculate from original dimensions
    if(width < height) {
        ratio = Math.min((width - 100) / original_canvas_width, 0.8);
    } else {
        ratio = Math.min((height - 200) / original_canvas_width, 0.8);
    }

    // Apply ratio to original dimensions
    canvas_width = Math.round(original_canvas_width * ratio);
    canvas_height = Math.round(original_canvas_height * ratio);
    radius_base = Math.round(original_radius_base * ratio);
    radius_handle = Math.round(original_radius_handle * ratio);
    radius_shaft = Math.round(original_radius_shaft * ratio);
    range = Math.round(original_range * ratio);
    step = Math.round(original_step * ratio);

    var canvas = document.getElementById("joystick");
    canvas.width = canvas_width;
    canvas.height = canvas_height;
 
    // Only add event listeners once
    if (!canvas.hasAttribute('data-events-added')) {
        canvas.addEventListener("touchstart", mouse_down, {passive: false});
        canvas.addEventListener("touchend", mouse_up, {passive: false});
        canvas.addEventListener("touchmove", mouse_move, {passive: false});
        canvas.addEventListener("mousedown", mouse_down);
        canvas.addEventListener("mouseup", mouse_up);
        canvas.addEventListener("mousemove", mouse_move);
        canvas.addEventListener("mouseleave", mouse_up);
        canvas.setAttribute('data-events-added', 'true');
    }

    var ctx = canvas.getContext("2d");
    // Reset context transformation before applying new one
    ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.translate(canvas_width/2, canvas_height/2);
    ctx.shadowBlur = 10;
    ctx.shadowColor = "LightGray";
    ctx.lineCap = "round";
    ctx.lineJoin = "round";

    update_view();
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

function connectWebSocket() {
    if(ws && ws.readyState === WebSocket.OPEN) {
        return;
    }
    
    if(isReconnecting) {
        return;
    }
    
    isReconnecting = true;

    var protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    var wsUrl = protocol + '//' + window.location.host + ':81';
    
    ws = new WebSocket(wsUrl);
    document.getElementById("connectionText").innerHTML = "Connecting...";
    
    ws.onopen = function() {
        isReconnecting = false;
        updateConnectionStatus('connected');
        
        // Request initial joystick configuration from Arduino
        ws.send('JOYSTICK:GET_CONFIG');
        console.log("Requesting initial joystick configuration...");
        
        // Request current joystick values from Arduino (if application supports it)
        setTimeout(function() {
            ws.send('JOYSTICK:GET_VALUES');
            console.log("Requesting current joystick values...");
        }, 100);
    };
    
    ws.onclose = function() {
        updateConnectionStatus('disconnected');
        ws = null;
        isReconnecting = false;
        
        // Auto-reconnect after 3 seconds
        setTimeout(function() {
            connectWebSocket();
        }, 3000);
    };
    
    ws.onerror = function(error) {
        console.error("WebSocket error:", error);
        var statusElement = document.getElementById("connectionStatus");
        statusElement.innerHTML = "Error";
        statusElement.className = "connection-status disconnected";
        
        isReconnecting = false;
        
        // Auto-reconnect after 3 seconds on error
        setTimeout(function() {
            connectWebSocket();
        }, 3000);
    };
    
    ws.onmessage = function(event) {
        console.log("Received:", event.data);
        parseJoystickResponse(event.data);
    };
}

function parseJoystickResponse(response) {
    // Handle joystick configuration response - format: JOYSTICK_CONFIG:{"autoReturn":true,"sensitivity":1.0}
    if (response.startsWith('JOYSTICK_CONFIG:')) {
        const configStr = response.substring(16); // Remove "JOYSTICK_CONFIG:" prefix
        try {
            const config = JSON.parse(configStr);
            console.log("Received joystick configuration:", config);
            
            // Update auto-return setting if provided
            if (config.hasOwnProperty('autoReturn')) {
                joystickConfig.autoReturn = config.autoReturn;
                document.getElementById("auto_return").textContent = config.autoReturn ? "ON" : "OFF";
                console.log("Auto-return set to:", config.autoReturn);
            }
            
            // Update sensitivity if provided
            if (config.hasOwnProperty('sensitivity')) {
                joystickConfig.sensitivity = config.sensitivity;
                document.getElementById("sensitivity").textContent = config.sensitivity.toFixed(1);
                console.log("Joystick sensitivity set to:", config.sensitivity);
            }
            
        } catch (e) {
            console.error('Error parsing joystick configuration:', e);
        }
        return;
    }
    
    // Handle joystick position updates from Arduino (for synchronization across tabs)
    if (response.startsWith('JOYSTICK:')) {
        const valuesStr = response.substring(9); // Remove "JOYSTICK:" prefix
        const values = valuesStr.split(',');
        
        if (values.length === 2) {
            const x = parseInt(values[0]);
            const y = parseInt(values[1]);
            
            if (!isNaN(x) && !isNaN(y)) {
                // Update joystick position without triggering send
                updateJoystickDisplayOnly(x, y);
                console.log('Joystick position updated from Arduino: X=' + x + ', Y=' + y);
            }
        }
        return;
    }
    
    // Handle other joystick responses if needed
    console.log("Unhandled joystick response:", response);
}

function send_data() {
    var currentTime = Date.now();
    if(currentTime - lastSentTime < sendInterval) {
        return; // Throttle sending to prevent flooding
    }

    var x = joystick.x, y = joystick.y;
    var joystick_range = range - radius_handle;
    
    // Convert to percentage values
    var x_percent = Math.round(x * 100 / joystick_range);
    var y_percent = Math.round(-y * 100 / joystick_range);
    
    // Check if change is significant enough based on sensitivity threshold
    var x_change = Math.abs(x_percent - lastSentValues.x);
    var y_change = Math.abs(y_percent - lastSentValues.y);
    
    if (x_change < joystickConfig.sensitivity && y_change < joystickConfig.sensitivity) {
        // Change is too small, don't send
        return;
    }
    
    lastSentTime = currentTime;
    lastSentValues.x = x_percent;
    lastSentValues.y = y_percent;

    // Update display with the actual percentage values
    document.getElementById("x_value").textContent = x_percent;
    document.getElementById("y_value").textContent = y_percent;

    if(ws && ws.readyState === WebSocket.OPEN) {
        var message = "JOYSTICK:" + x_percent + "," + y_percent;
        ws.send(message);
        console.log("Sent to Arduino - Values:", x_percent + "," + y_percent, "| Change:", x_change.toFixed(1) + "," + y_change.toFixed(1), "| Sensitivity threshold:", joystickConfig.sensitivity);
    }
}

function update_view() {
    var x = joystick.x, y = joystick.y;
    var canvas = document.getElementById("joystick");
    var ctx = canvas.getContext("2d");

    ctx.clearRect(-canvas_width/2, -canvas_height/2, canvas_width, canvas_height);

    // Draw outer boundary
    ctx.lineWidth = 3;
    ctx.strokeStyle = "gray";
    ctx.fillStyle = "LightGray";
    ctx.beginPath();
    ctx.arc(0, 0, range, 0, 2 * Math.PI);
    ctx.stroke();
    ctx.fill();

    // Draw base
    ctx.strokeStyle = "black";
    ctx.fillStyle = "hsl(0, 0%, 35%)";
    ctx.beginPath();
    ctx.arc(0, 0, radius_base, 0, 2 * Math.PI);
    ctx.stroke();
    ctx.fill();

    // Draw shaft (original 3D effect)
    ctx.strokeStyle = "red";

    var lineWidth = radius_shaft;
    var pre_x = 0, pre_y = 0;
    var x_end = x/5;
    var y_end = y/5;
    var max_count = (radius_shaft - 10)/step;
    var count = 1;

    while(lineWidth >= 10) {
        var cur_x = Math.round(count * x_end / max_count);
        var cur_y = Math.round(count * y_end / max_count);
        
        ctx.lineWidth = lineWidth;
        ctx.beginPath();
        ctx.lineTo(pre_x, pre_y);
        ctx.lineTo(cur_x, cur_y);
        ctx.stroke();

        lineWidth -= step;
        pre_x = cur_x;
        pre_y = cur_y;
        count++;
    }

    var x_start = Math.round(x / 3);
    var y_start = Math.round(y / 3);
    lineWidth += step;

    ctx.beginPath();
    ctx.lineTo(pre_x, pre_y);
    ctx.lineTo(x_start, y_start);
    ctx.stroke();

    count = 1;
    pre_x = x_start;
    pre_y = y_start;

    while(lineWidth < radius_shaft) {
        var cur_x = Math.round(x_start + count * (x - x_start) / max_count);
        var cur_y = Math.round(y_start + count * (y - y_start) / max_count);
        
        ctx.lineWidth = lineWidth;
        ctx.beginPath();
        ctx.lineTo(pre_x, pre_y);
        ctx.lineTo(cur_x, cur_y);
        ctx.stroke();

        lineWidth += step;
        pre_x = cur_x;
        pre_y = cur_y;
        count++;
    }

    // Draw handle with original gradient
    var grd = ctx.createRadialGradient(x, y, 0, x, y, radius_handle);
    for(var i = 85; i >= 50; i-=5)
        grd.addColorStop((85 - i)/35, "hsl(0, 100%, "+ i + "%)");

    ctx.fillStyle = grd;
    ctx.beginPath();
    ctx.arc(x, y, radius_handle, 0, 2 * Math.PI);
    ctx.fill();
}

function process_event(event) {
    var rect = event.target.getBoundingClientRect();
    var pos_x, pos_y;
    
    if(event.touches && event.touches.length > 0) {
        pos_x = (event.touches[0].clientX - rect.left) - canvas_width/2;
        pos_y = (event.touches[0].clientY - rect.top) - canvas_height/2;
    } else {
        pos_x = (event.clientX - rect.left) - canvas_width/2;
        pos_y = (event.clientY - rect.top) - canvas_height/2;
    }

    return {x: pos_x, y: pos_y};
}

function mouse_down(event) {
    event.preventDefault();

    var pos = process_event(event);
    
    // Check if click is within the joystick base area
    var radius = Math.sqrt(pos.x*pos.x + pos.y*pos.y);
    if(radius > range)
        return;

    // Only allow dragging if click is within the handle/thumb area
    var delta_x = pos.x - joystick.x;
    var delta_y = pos.y - joystick.y;
    var dist = Math.sqrt(delta_x*delta_x + delta_y*delta_y);
    
    if(dist > radius_handle)
        return; // Click is not on the handle, ignore

    // Click is on the handle, enable dragging
    click_state = 1;
}

function mouse_up(event) {
    if(event) event.preventDefault();
    
    if(click_state) {
        click_state = 0;
        
        // Check if auto return to center is enabled
        if(joystickConfig.autoReturn) {
            // Return to center with smooth animation
            var steps = 10;
            var stepX = joystick.x / steps;
            var stepY = joystick.y / steps;
            var currentStep = 0;
            
            var returnToCenter = setInterval(function() {
                currentStep++;
                joystick.x -= stepX;
                joystick.y -= stepY;
                
                if(currentStep >= steps) {
                    joystick.x = 0;
                    joystick.y = 0;
                    clearInterval(returnToCenter);
                }
                
                send_data();
                update_view();
            }, 20);
        }
    }
}

function mouse_move(event) {
    event.preventDefault();

    if(!click_state)
        return;

    var pos = process_event(event);
    var radius = Math.sqrt(pos.x*pos.x + pos.y*pos.y);

    if(joystickConfig.autoReturn) {
        // Auto-return mode: restrict movement to within range
        if(radius < (range - radius_handle)) {
            joystick = pos;
            send_data();
            update_view();
        }
    } else {
        // Manual mode: allow movement to any position within range
        if(radius < (range - radius_handle)) {
            joystick = pos;
        } else {
            // If drag goes beyond range, clamp to edge
            var angle = Math.atan2(pos.y, pos.x);
            var maxRadius = range - radius_handle;
            joystick.x = Math.cos(angle) * maxRadius;
            joystick.y = Math.sin(angle) * maxRadius;
        }
        send_data();
        update_view();
    }
}

function resetJoystick() {
    joystick.x = 0;
    joystick.y = 0;
    send_data();
    update_view();
}

function updateJoystickDisplayOnly(x, y) {
    // Update joystick position from server without triggering WebSocket send
    // Convert from percentage values (-100 to 100) back to canvas coordinates
    var joystick_range = range - radius_handle;
    
    // Clamp values to valid range
    x = Math.max(-100, Math.min(100, x));
    y = Math.max(-100, Math.min(100, y));
    
    // Convert percentage to canvas coordinates
    var canvas_x = Math.round(x * joystick_range / 100);
    var canvas_y = Math.round(-y * joystick_range / 100); // Invert Y to match canvas coordinates
    
    // Additional boundary check to ensure joystick stays within limits
    var radius = Math.sqrt(canvas_x * canvas_x + canvas_y * canvas_y);
    if (radius > joystick_range) {
        var angle = Math.atan2(canvas_y, canvas_x);
        canvas_x = Math.cos(angle) * joystick_range;
        canvas_y = Math.sin(angle) * joystick_range;
    }
    
    joystick.x = canvas_x;
    joystick.y = canvas_y;
    
    // Calculate the actual percentage values from joystick position for display
    // Use the same formula as send_data() to ensure consistency
    var display_x_percent = Math.round(canvas_x * 100 / joystick_range);
    var display_y_percent = Math.round(-canvas_y * 100 / joystick_range);
    
    // Update display values with calculated percentages (not the received values)
    document.getElementById("x_value").textContent = display_x_percent;
    document.getElementById("y_value").textContent = display_y_percent;
    
    // Redraw joystick position (without triggering send_data)
    update_view();
}

window.onload = function() {
    init();
    update_view();
    setTimeout(connectWebSocket, 100);
};

// Throttled resize handler to prevent excessive calls during scroll
window.onresize = function() {
    var now = Date.now();
    if (now - lastResizeTime > 200) { // Only resize if 200ms passed
        lastResizeTime = now;
        setTimeout(function() {
            init();
            update_view();
            if (!ws || ws.readyState !== WebSocket.OPEN) {
                connectWebSocket();
            }
        }, 100);
    }
};
</script>
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
        <h1>🕹️ Web Joystick Control</h1>
        <p>Interactive joystick for remote Arduino control</p>
    </div>

    <div class="content" style="flex: 1;">
        <div class="joystick-section">
            
            <div class="joystick-container">
                <canvas id="joystick" class="joystick-canvas"></canvas>
            </div>
            
            <div class="controls-panel">
                <div class="controls-grid">
                    <div class="control-item">
                        <div class="coordinate-label">X Position</div>
                        <div class="coordinate-display" id="x_value">0</div>
                    </div>
                    <div class="control-item">
                        <div class="coordinate-label">Y Position</div>
                        <div class="coordinate-display" id="y_value">0</div>
                    </div>
                </div>
                
                <div style="display: flex; justify-content: center; gap: 15px; margin: 10px 0; font-size: 0.85em;">
                    <span style="color: #666;">Config:</span>
                    <span style="color: #667eea;">Auto Return: <strong id="auto_return">---</strong></span>
                    <span style="color: #667eea;">Sensitivity: <strong id="sensitivity">---</strong></span>
                </div>
            </div>
        </div>
    </div>
    
    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>
</div>
</body>
</html>
)RAWSTRING";

#endif
