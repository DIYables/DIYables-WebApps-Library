#ifndef WEB_PLOTTER_HTML_H
#define WEB_PLOTTER_HTML_H

const char WEB_PLOTTER_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Real-time Data Plotter - DIYables WebApp</title>
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
            margin: 0;
            padding: 0 0 40px 0;
            display: flex;
            flex-direction: column;
        }
        
        .container {
            background: white;
            border-radius: 0;
            box-shadow: none;
            width: 100%;
            flex: 1;
            max-width: 1400px;
            margin: 0 auto;
            padding: 20px;
            text-align: center;
            display: flex;
            flex-direction: column;
            justify-content: flex-start;
        }
        
        .header {
            margin-top: 20px;
            margin-bottom: 30px;
            position: relative;
        }
        
        .header h1 {
            font-size: 2.0em;
            font-weight: 700;
            color: #333;
            margin-bottom: 10px;
            line-height: 1.2;
        }
        
        .header p {
            font-size: 1.1em;
            color: #666;
            margin-bottom: 20px;
        }
        
        .top-nav {
            background: #f8f9fa;
            padding: 10px 20px;
            border-bottom: 1px solid #e9ecef;
            margin: -20px -20px 0 -20px;
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
            margin: 0 -20px 20px -20px;
            text-align: center;
            font-size: 0.9em;
            color: black;
        }
        
        .websocket-status #connectionText {
            font-weight: bold;
        }
        
        .plot-area {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            background: #f8f9fa;
            border-radius: 12px;
            padding: 20px;
            margin: 20px 0;
            min-height: 500px;
        }
        
        #graph {
            border: 2px solid #dee2e6;
            border-radius: 8px;
            background: white;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
        }
        
        .controls {
            display: flex;
            gap: 15px;
            margin-top: 20px;
            justify-content: center;
            align-items: center;
            flex-wrap: wrap;
        }
        
        .plot-info {
            display: flex;
            gap: 20px;
            margin-top: 15px;
            justify-content: center;
            align-items: center;
            flex-wrap: wrap;
            font-size: 14px;
            color: #666;
        }
        
        .plot-info > span {
            background: white;
            padding: 8px 12px;
            border-radius: 6px;
            border: 1px solid #dee2e6;
        }
        
        .plot-info span span {
            background: none;
            padding: 0;
            border-radius: 0;
            border: none;
            color: #007bff;
        }
        
        .legend {
            display: flex;
            gap: 15px;
            margin-top: 15px;
            justify-content: center;
            align-items: center;
            flex-wrap: wrap;
        }
        
        .legend-item {
            display: flex;
            align-items: center;
            gap: 8px;
            padding: 6px 12px;
            background: white;
            border-radius: 6px;
            border: 1px solid #dee2e6;
            font-size: 14px;
        }
        
        .legend-color {
            width: 12px;
            height: 12px;
            border-radius: 2px;
        }
        
        @media (max-width: 768px) {
            .container {
                padding: 15px;
            }
            
            .header h1 {
                font-size: 1.6em;
            }
            
            .top-nav {
                margin: -15px -15px 0 -15px;
                padding: 10px 15px;
            }
            
            .websocket-status {
                margin: 0 -15px 20px -15px;
            }
            
            .controls {
                flex-direction: column;
                gap: 10px;
            }
            
            .plot-info {
                flex-direction: column;
                gap: 10px;
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
            <h1 id="plotTitle">📊 Real-time Data Plotter</h1>
            <p>Visualize your Arduino sensor data in real-time</p>
        </div>
        
        <div class="plot-area">
            <canvas id="graph"></canvas>
            <div class="plot-info">
                <span>Samples: <span id="sampleCount">0</span></span>
                <span>Data Lines: <span id="lineCount">0</span></span>
                <span>Auto Scale: <span id="autoScaleStatus">Enabled</span></span>
            </div>
            <div class="legend" id="legend"></div>
        </div>
    </div>

    <script>
        // Configuration variables
        var COLOR_BACKGROUND = "#FFFFFF";
        var COLOR_TEXT = "#333333";
        var COLOR_BOUND = "#666666";
        var COLOR_GRIDLINE = "#E9ECEF";
        var COLOR_LINE = ["#007BFF", "#DC3545", "#28A745", "#FFC107", "#6F42C1", "#17A2B8", "#FD7E14", "#20C997"];

        var LEGEND_WIDTH = 12;
        var X_AXIS_TITLE_HEIGHT = 40;
        var Y_AXIS_TITLE_WIDTH = 40;
        var X_AXIS_VALUE_HEIGHT = 40;
        var Y_AXIS_VALUE_WIDTH = 60;
        var PLOT_AREA_PADDING_TOP = 30;
        var PLOT_AREA_PADDING_RIGHT = 30;
        var X_GRIDLINE_NUM = 5;
        var Y_GRIDLINE_NUM = 4;

        var WSP_SIZE_TYPE = 1; // 0: Fixed size, 1: responsive
        var WSP_WIDTH = 800;
        var WSP_HEIGHT = 400;
        var MAX_SAMPLE = 50;
        var X_AXIS_MIN = 0;
        var X_AXIS_MAX = MAX_SAMPLE;
        var Y_AXIS_AUTO_SCALE = 1;
        var Y_AXIS_MIN = -5;
        var Y_AXIS_MAX = 5;
        var X_AXIS_TITLE = "Samples";
        var Y_AXIS_TITLE = "Values";
        var PLOT_TITLE = "Arduino - Web Plotter";

        var plot_area_width;
        var plot_area_height;
        var plot_area_pivot_x;
        var plot_area_pivot_y;

        var sample_count = 0;
        var buffer = "";
        var data = [];
        var ws;
        var canvas;
        var ctx;

        function init() {
            canvas = document.getElementById("graph");
            canvas.style.backgroundColor = COLOR_BACKGROUND;
            ctx = canvas.getContext("2d");
            canvas_resize();
            setInterval(update_view, 1000 / 30); // 30 FPS
            
            // Auto-connect on load
            setTimeout(() => {
                if (!ws) {
                    connect();
                }
            }, 1000);
        }

        function connect() {
            try {
                ws = new WebSocket("ws://" + window.location.host + ":81");
                updateConnectionStatus("connecting");
                
                ws.onopen = function() {
                    updateConnectionStatus("connected");
                    
                    // Request initial configuration
                    ws.send("PLOTTER:GET_CONFIG");
                };
                
                ws.onclose = function() {
                    updateConnectionStatus("disconnected");
                    ws = null;
                    
                    // Auto-reconnect after 3 seconds
                    setTimeout(() => {
                        if (!ws) {
                            connect();
                        }
                    }, 3000);
                };
                
                ws.onmessage = function(e) {
                    handleWebSocketMessage(e.data);
                };
                
                ws.onerror = function(error) {
                    console.error("WebSocket error:", error);
                    updateConnectionStatus("disconnected");
                };
                
            } catch (error) {
                console.error("Failed to connect:", error);
                updateConnectionStatus("disconnected");
            }
        }

        function disconnect() {
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

        function handleWebSocketMessage(message) {
            console.log("Received:", message);
            
            if (message.startsWith("PLOTTER_DATA:")) {
                const dataStr = message.substring(13);
                processPlotData(dataStr);
            } else if (message.startsWith("PLOTTER_CONFIG:")) {
                const configStr = message.substring(15);
                processConfiguration(configStr);
            }
        }

        function processPlotData(dataStr) {
            buffer += dataStr + "\n";
            
            // Process complete lines
            while (buffer.indexOf("\n") > 0) {
                const pos = buffer.indexOf("\n");
                const line = buffer.substring(0, pos).trim();
                buffer = buffer.substring(pos + 1);
                
                if (line.length === 0) continue;
                
                // Parse the data line
                const values = [];
                const parts = line.split(/[\s\t]+/);
                
                for (let i = 0; i < parts.length; i++) {
                    const value = parseFloat(parts[i]);
                    if (!isNaN(value)) {
                        values.push(value);
                    }
                }
                
                if (values.length === 0) continue;
                
                // Add values to data arrays
                for (let i = 0; i < values.length; i++) {
                    if (i >= data.length) {
                        data.push([]);
                    }
                    data[i].push(values[i]);
                }
                
                sample_count++;
                
                // Limit data size
                for (let line = 0; line < data.length; line++) {
                    while (data[line].length > MAX_SAMPLE) {
                        data[line].shift();
                    }
                }
                
                if (Y_AXIS_AUTO_SCALE) {
                    auto_scale();
                }
                
                updateUI();
            }
        }

        function processConfiguration(configStr) {
            const parts = configStr.split("|");
            if (parts.length >= 7) {
                PLOT_TITLE = parts[0];
                X_AXIS_TITLE = parts[1];
                Y_AXIS_TITLE = parts[2];
                Y_AXIS_MIN = parseFloat(parts[3]);
                Y_AXIS_MAX = parseFloat(parts[4]);
                Y_AXIS_AUTO_SCALE = parseInt(parts[5]);
                MAX_SAMPLE = parseInt(parts[6]);
                
                canvas_resize();
                updateUI();
            }
        }

        function updateUI() {
            document.getElementById("plotTitle").textContent = "📊 " + PLOT_TITLE;
            document.getElementById("sampleCount").textContent = sample_count;
            document.getElementById("lineCount").textContent = data.length;
            document.getElementById("autoScaleStatus").textContent = Y_AXIS_AUTO_SCALE ? "Enabled" : "Disabled";
            updateLegend();
        }

        function updateLegend() {
            const legend = document.getElementById("legend");
            legend.innerHTML = "";
            
            for (let i = 0; i < data.length; i++) {
                const item = document.createElement("div");
                item.className = "legend-item";
                
                const color = document.createElement("div");
                color.className = "legend-color";
                color.style.backgroundColor = COLOR_LINE[i % COLOR_LINE.length];
                
                const label = document.createElement("span");
                label.textContent = `Data ${i + 1}`;
                
                item.appendChild(color);
                item.appendChild(label);
                legend.appendChild(item);
            }
        }

        function map(x, in_min, in_max, out_min, out_max) {
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }

        function update_view() {
            if (sample_count <= MAX_SAMPLE) {
                X_AXIS_MAX = Math.max(sample_count, 10);
            } else {
                X_AXIS_MAX = MAX_SAMPLE;
            }

            ctx.clearRect(0, 0, WSP_WIDTH, WSP_HEIGHT);
            ctx.save();
            ctx.translate(plot_area_pivot_x, plot_area_pivot_y);

            // Draw axes and grid
            drawAxes();
            
            // Draw data lines
            drawDataLines();
            
            ctx.restore();
        }

        function drawAxes() {
            ctx.font = "14px Arial";
            ctx.textBaseline = "middle";
            ctx.textAlign = "center";
            ctx.fillStyle = COLOR_TEXT;

            // X axis title
            if (X_AXIS_TITLE !== "") {
                ctx.fillText(X_AXIS_TITLE, plot_area_width / 2, X_AXIS_VALUE_HEIGHT + X_AXIS_TITLE_HEIGHT / 2);
            }

            // Y axis title
            if (Y_AXIS_TITLE !== "") {
                ctx.save();
                ctx.rotate(-90 * Math.PI / 180);
                ctx.fillText(Y_AXIS_TITLE, plot_area_height / 2, -Y_AXIS_VALUE_WIDTH - Y_AXIS_TITLE_WIDTH / 2);
                ctx.restore();
            }

            ctx.font = "12px Arial";
            ctx.strokeStyle = COLOR_BOUND;
            ctx.lineWidth = 1;

            // Y grid lines and labels
            ctx.textAlign = "right";
            for (let i = 0; i <= Y_GRIDLINE_NUM; i++) {
                const y_gridline_px = -map(i, 0, Y_GRIDLINE_NUM, 0, plot_area_height);
                const y_pos = Math.round(y_gridline_px) + 0.5;
                
                // Grid line
                ctx.strokeStyle = COLOR_GRIDLINE;
                ctx.beginPath();
                ctx.moveTo(0, y_pos);
                ctx.lineTo(plot_area_width, y_pos);
                ctx.stroke();
                
                // Axis tick
                ctx.strokeStyle = COLOR_BOUND;
                ctx.beginPath();
                ctx.moveTo(-7, y_pos);
                ctx.lineTo(4, y_pos);
                ctx.stroke();
                
                // Label
                const y_value = map(i, 0, Y_GRIDLINE_NUM, Y_AXIS_MIN, Y_AXIS_MAX);
                ctx.fillStyle = COLOR_TEXT;
                ctx.fillText(y_value.toFixed(1), -15, y_pos);
            }

            // X grid lines and labels
            ctx.textAlign = "center";
            for (let i = 0; i <= X_GRIDLINE_NUM; i++) {
                const x_gridline_px = map(i, 0, X_GRIDLINE_NUM, 0, plot_area_width);
                const x_pos = Math.round(x_gridline_px) + 0.5;
                
                // Grid line
                ctx.strokeStyle = COLOR_GRIDLINE;
                ctx.beginPath();
                ctx.moveTo(x_pos, 0);
                ctx.lineTo(x_pos, -plot_area_height);
                ctx.stroke();
                
                // Axis tick
                ctx.strokeStyle = COLOR_BOUND;
                ctx.beginPath();
                ctx.moveTo(x_pos, 7);
                ctx.lineTo(x_pos, -4);
                ctx.stroke();
                
                // Label
                let x_value;
                if (sample_count <= MAX_SAMPLE) {
                    x_value = map(i, 0, X_GRIDLINE_NUM, X_AXIS_MIN, X_AXIS_MAX);
                } else {
                    x_value = map(i, 0, X_GRIDLINE_NUM, sample_count - MAX_SAMPLE, sample_count);
                }
                ctx.fillStyle = COLOR_TEXT;
                ctx.fillText(Math.round(x_value).toString(), x_pos, X_AXIS_VALUE_HEIGHT / 2 + 5);
            }

            // Draw axes
            ctx.strokeStyle = COLOR_BOUND;
            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(plot_area_width, 0);
            ctx.moveTo(0, 0);
            ctx.lineTo(0, -plot_area_height);
            ctx.stroke();
        }

        function drawDataLines() {
            ctx.lineWidth = 2;
            
            for (let line = 0; line < data.length; line++) {
                const lineData = data[line];
                if (lineData.length < 2) continue;
                
                ctx.strokeStyle = COLOR_LINE[line % COLOR_LINE.length];
                ctx.beginPath();
                
                for (let i = 0; i < lineData.length; i++) {
                    const x_px = map(i, 0, Math.max(lineData.length - 1, 1), 0, plot_area_width);
                    const y_px = -map(lineData[i], Y_AXIS_MIN, Y_AXIS_MAX, 0, plot_area_height);
                    
                    if (i === 0) {
                        ctx.moveTo(x_px, y_px);
                    } else {
                        ctx.lineTo(x_px, y_px);
                    }
                }
                
                ctx.stroke();
            }
        }

        function canvas_resize() {
            // Save current scroll position
            const scrollTop = window.pageYOffset || document.documentElement.scrollTop;
            
            if (WSP_SIZE_TYPE) {
                const container = canvas.parentElement;
                const containerRect = container.getBoundingClientRect();
                WSP_WIDTH = Math.min(containerRect.width - 40, 1200);
                WSP_HEIGHT = Math.min(window.innerHeight * 0.6, 500);
            }

            canvas.width = WSP_WIDTH;
            canvas.height = WSP_HEIGHT;

            // Calculate plot area dimensions
            ctx.font = "12px Arial";
            const y_min_text = ctx.measureText(Y_AXIS_MIN.toFixed(1)).width;
            const y_max_text = ctx.measureText(Y_AXIS_MAX.toFixed(1)).width;
            Y_AXIS_VALUE_WIDTH = Math.max(y_min_text, y_max_text) + 20;

            plot_area_width = WSP_WIDTH - Y_AXIS_VALUE_WIDTH - PLOT_AREA_PADDING_RIGHT;
            plot_area_height = WSP_HEIGHT - X_AXIS_VALUE_HEIGHT - PLOT_AREA_PADDING_TOP;
            plot_area_pivot_x = Y_AXIS_VALUE_WIDTH;
            plot_area_pivot_y = WSP_HEIGHT - X_AXIS_VALUE_HEIGHT;

            if (X_AXIS_TITLE !== "") {
                plot_area_height -= X_AXIS_TITLE_HEIGHT;
                plot_area_pivot_y -= X_AXIS_TITLE_HEIGHT;
            }

            if (Y_AXIS_TITLE !== "") {
                plot_area_width -= Y_AXIS_TITLE_WIDTH;
                plot_area_pivot_x += Y_AXIS_TITLE_WIDTH;
            }

            ctx.lineWidth = 1;
        }

        function auto_scale() {
            if (data.length === 0) return;
            
            let all_values = [];
            for (let i = 0; i < data.length; i++) {
                all_values = all_values.concat(data[i]);
            }
            
            if (all_values.length === 0) return;
            
            const max = Math.max(...all_values);
            const min = Math.min(...all_values);
            const MIN_DELTA = 2.0;
            
            let range = max - min;
            if (range < MIN_DELTA) {
                const mid = (max + min) / 2;
                Y_AXIS_MAX = mid + MIN_DELTA / 2;
                Y_AXIS_MIN = mid - MIN_DELTA / 2;
            } else {
                const padding = range * 0.1;
                Y_AXIS_MAX = max + padding;
                Y_AXIS_MIN = min - padding;
            }
            
            canvas_resize();
        }

        window.onload = init;
        window.onresize = canvas_resize;
    </script>
    
    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>
</body>
</html>
)HTMLDELIM";

#endif
