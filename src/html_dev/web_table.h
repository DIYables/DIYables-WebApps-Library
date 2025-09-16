#ifndef WEB_TABLE_HTML_H
#define WEB_TABLE_HTML_H

const char WEB_TABLE_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Remote Data Table - DIYables WebApp</title>
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
            padding: 0 0 40px 0;
            display: flex;
            flex-direction: column;
            box-sizing: border-box;
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
        
        .controls {
            padding: 20px;
            margin-bottom: 30px;
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 20px;
        }
        
        .table-container {
            width: 100%;
            max-width: 900px;
            margin: 0 auto;
            background: white;
            box-shadow: 0 15px 35px rgba(0,0,0,0.1), 0 5px 15px rgba(0,0,0,0.07);
            overflow: hidden;
            border: 2px solid rgba(102, 126, 234, 0.1);
        }
        
        .data-table {
            width: 100%;
            border-collapse: collapse;
            font-size: 1.0em;
            background: linear-gradient(145deg, #ffffff 0%, #f8f9ff 100%);
        }
        
        .data-table thead {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
        }
        
        .data-table th {
            padding: 25px 20px;
            text-align: left;
            font-weight: 700;
            font-size: 1.2em;
            text-transform: uppercase;
            letter-spacing: 2px;
            text-shadow: 0 2px 4px rgba(0,0,0,0.2);
            position: relative;
        }
        
        .data-table th:first-child {
            text-align: right;
            width: 40%;
        }
        
        .data-table th:last-child {
            text-align: left;
        }
        
        .data-table th::after {
            content: '';
            position: absolute;
            bottom: 0;
            left: 0;
            right: 0;
            height: 3px;
            background: linear-gradient(90deg, transparent 0%, rgba(255,255,255,0.3) 50%, transparent 100%);
        }
        
        .data-table tbody tr {
            transition: all 0.3s ease;
            border-bottom: 1px solid rgba(102, 126, 234, 0.1);
        }
        
        .data-table tbody tr:hover {
            background: linear-gradient(135deg, #f0f4ff 0%, #e8f2ff 100%);
            transform: scale(1.01);
            box-shadow: inset 0 0 20px rgba(102, 126, 234, 0.1);
        }
        
        .data-table tbody tr:nth-child(even) {
            background: linear-gradient(135deg, #fafbff 0%, #f5f7ff 100%);
        }
        
        .data-table tbody tr:nth-child(even):hover {
            background: linear-gradient(135deg, #f0f4ff 0%, #e8f2ff 100%);
        }
        
        .data-table td {
            padding: 20px;
            vertical-align: middle;
            border-bottom: 1px solid rgba(102, 126, 234, 0.08);
        }
        
        .data-table td.attribute {
            font-weight: 700;
            color: #4a5568;
            background: linear-gradient(135deg, #f8f9ff 0%, #f0f4ff 100%);
            width: 40%;
            font-size: 1.05em;
            border-right: 3px solid rgba(102, 126, 234, 0.2);
            text-shadow: 0 1px 2px rgba(0,0,0,0.05);
            text-align: right;
        }
        
        .data-table td.value {
            font-family: 'Courier New', monospace;
            color: #dc3545;
            font-size: 1.1em;
            font-weight: 600;
            text-shadow: 0 1px 2px rgba(220, 53, 69, 0.2);
            text-align: left;
        }
        
        .value-highlight {
            animation: highlight 1.5s ease-out;
            border-left: 3px solid #dc3545;
            background-color: rgba(220, 53, 69, 0.1);
            transition: all 0.3s ease;
        }
        
        .value-highlight-light {
            animation: highlight-light 1s ease-out;
            border-left: 3px solid #667eea;
            background-color: rgba(102, 126, 234, 0.1);
            transition: all 0.3s ease;
        }
        
        @keyframes highlight {
            0% { 
                border-left-color: #dc3545;
                background-color: rgba(220, 53, 69, 0.1);
            }
            50% { 
                border-left-color: #f56565;
                background-color: rgba(220, 53, 69, 0.2);
            }
            100% { 
                border-left-color: #dc3545;
                background-color: rgba(220, 53, 69, 0.1);
            }
        }
        
        @keyframes highlight-light {
            0% { 
                border-left-color: #667eea;
                background-color: rgba(102, 126, 234, 0.1);
            }
            50% { 
                border-left-color: #4f46e5;
                background-color: rgba(102, 126, 234, 0.2);
            }
            100% { 
                border-left-color: #667eea;
                background-color: rgba(102, 126, 234, 0.1);
            }
        }
        
        .empty-state {
            text-align: center;
            padding: 60px 20px;
            color: #666;
        }
        
        .empty-state h3 {
            font-size: 1.5em;
            margin-bottom: 10px;
            color: #888;
        }
        
        .empty-state p {
            font-size: 1.1em;
            line-height: 1.6;
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
        
        /* Mobile responsiveness */
        @media (max-width: 768px) {
            body {
                padding-bottom: 80px;
            }
            
            .header h1 {
                font-size: 2em;
            }
            
            .data-table {
                font-size: 1em;
            }
            
            .data-table th {
                padding: 15px 10px;
                font-size: 1.1em;
            }
            
            .data-table td {
                padding: 12px 10px;
            }
            
            .data-table td.attribute {
                width: 45%;
            }
            
            .footer {
                height: 50px;
                padding: 10px 15px;
                font-size: 0.8em;
            }
        }
        
        @media (max-width: 480px) {
            .header h1 {
                font-size: 1.8em;
            }
            
            .data-table {
                font-size: 0.95em;
            }
            
            .data-table th {
                padding: 12px 8px;
                font-size: 1em;
            }
            
            .data-table td {
                padding: 10px 8px;
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
        
        <div class="websocket-status" id="websocketStatus">
            WebSocket: <span id="connectionText">Disconnected</span>
        </div>
        
        <div class="header">
            <h1>📊 Remote Data Table</h1>
            <p>Real-time data monitoring with dynamic value updates</p>
        </div>
        
        <div class="controls">
            <div class="table-container">
                <table class="data-table" id="dataTable">
                    <thead>
                        <tr>
                            <th>Attribute</th>
                            <th>Value</th>
                        </tr>
                    </thead>
                    <tbody id="tableBody">
                        <tr>
                            <td colspan="2" class="empty-state">
                                <h3>No Data Available</h3>
                                <p>Waiting for data from Arduino...</p>
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    </div>

    <script>
        let socket;
        let isConnected = false;
        let tableData = [];
        
        // Track previous values to detect changes
        const previousValues = new Map();
        
        // Track update frequency to distinguish dynamic vs static attributes
        const updateCounts = new Map();
        
        // Initialize WebSocket connection
        function initWebSocket() {
            const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
            const wsPort = ':81';  // Fixed WebSocket port
            const socketURL = protocol + '//' + window.location.hostname + wsPort + '/ws';
            
            socket = new WebSocket(socketURL);
            
            socket.onopen = function(event) {
                isConnected = true;
                updateConnectionStatus('connected');
                requestTableConfig();
                requestTableData();
            };
            
            socket.onmessage = function(event) {
                console.log('WebSocket message received:', event.data);
                handleWebSocketMessage(event.data);
            };
            
            socket.onclose = function(event) {
                isConnected = false;
                updateConnectionStatus('disconnected');
                
                // Attempt to reconnect after 3 seconds
                setTimeout(initWebSocket, 3000);
            };
            
            socket.onerror = function(error) {
                console.error('WebSocket error:', error);
                isConnected = false;
                updateConnectionStatus('disconnected');
            };
        }
        
        // Update connection status display
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
        
        // Request table configuration from Arduino
        function requestTableConfig() {
            if (!isConnected || socket.readyState !== WebSocket.OPEN) {
                return;
            }
            socket.send('TABLE:GET_CONFIG');
        }
        
        // Handle incoming WebSocket messages
        function handleWebSocketMessage(message) {
            if (message.startsWith('TABLE_CONFIG:')) {
                const configData = message.substring(13); // Remove "TABLE_CONFIG:"
                parseTableConfig(configData);
            } else if (message.startsWith('TABLE_DATA:')) {
                const data = message.substring(11); // Remove "TABLE_DATA:"
                parseTableData(data);
            } else if (message.startsWith('VALUE_UPDATE:')) {
                const updateData = message.substring(13); // Remove "VALUE_UPDATE:"
                const colonIndex = updateData.indexOf(':');
                if (colonIndex > 0) {
                    const attribute = updateData.substring(0, colonIndex);
                    const value = updateData.substring(colonIndex + 1);
                    updateTableValue(attribute, value);
                }
            }
        }
        
        // Parse table configuration from Arduino
        function parseTableConfig(configData) {
            try {
                // Parse JSON array of attributes
                const attributes = JSON.parse(configData);
                tableData = [];
                // Clear tracking data when table structure changes
                previousValues.clear();
                updateCounts.clear();
                
                for (const attr of attributes) {
                    tableData.push({ attribute: attr, value: 'Loading...' });
                }
                renderTable();
            } catch (e) {
                console.error('Error parsing table config:', e);
            }
        }
        
        // Parse table data from Arduino
        function parseTableData(data) {
            tableData = [];
            if (data && data.length > 0) {
                const rows = data.split('|');
                for (const row of rows) {
                    const colonIndex = row.indexOf(':');
                    if (colonIndex > 0) {
                        const attribute = row.substring(0, colonIndex);
                        const value = row.substring(colonIndex + 1);
                        tableData.push({ attribute: attribute, value: value });
                    }
                }
            }
            renderTable();
        }
        
        // Update a specific value in the table
        function updateTableValue(attribute, value) {
            // Get previous value for comparison
            const previousValue = previousValues.get(attribute);
            const hasChanged = previousValue !== undefined && previousValue !== value;
            
            // Debug logging
            console.log(`Update: ${attribute} = "${value}" (was: "${previousValue}") -> ${hasChanged ? 'CHANGED' : 'SAME'}`);
            
            // Update tracking data
            previousValues.set(attribute, value);
            updateCounts.set(attribute, (updateCounts.get(attribute) || 0) + 1);
            
            // Find and update the value in tableData
            for (let i = 0; i < tableData.length; i++) {
                if (tableData[i].attribute === attribute) {
                    tableData[i].value = value;
                    break;
                }
            }
            
            // Update ONLY the specific row instead of re-rendering entire table
            updateSingleRow(attribute, value, hasChanged, previousValue);
        }
        
        // Update a single table row without re-rendering the entire table
        function updateSingleRow(attribute, value, hasChanged, previousValue) {
            const rows = document.querySelectorAll('#tableBody tr');
            for (const row of rows) {
                const attrCell = row.querySelector('.attribute');
                if (attrCell && attrCell.textContent === attribute) {
                    const valueCell = row.querySelector('.value');
                    if (valueCell) {
                        // Clear any existing timeouts for this cell
                        if (valueCell._highlightTimeout) {
                            clearTimeout(valueCell._highlightTimeout);
                            valueCell._highlightTimeout = null;
                        }
                        
                        // Update the text content
                        valueCell.textContent = value;
                        
                        // Remove existing classes and force reflow to restart animation
                        valueCell.classList.remove('value-highlight', 'value-highlight-light');
                        void valueCell.offsetWidth; // Force reflow
                        
                        if (hasChanged) {
                            // Big highlight for changed values (red)
                            valueCell.classList.add('value-highlight');
                            valueCell._highlightTimeout = setTimeout(() => {
                                valueCell.classList.remove('value-highlight');
                                valueCell._highlightTimeout = null;
                            }, 1500);
                        } else if (previousValue !== undefined) {
                            // Light highlight for unchanged values (blue)
                            valueCell.classList.add('value-highlight-light');
                            valueCell._highlightTimeout = setTimeout(() => {
                                valueCell.classList.remove('value-highlight-light');
                                valueCell._highlightTimeout = null;
                            }, 1000);
                        }
                        // No highlight for first-time values (initial load)
                    }
                    break;
                }
            }
        }
        
        // Render the table with current data
        function renderTable() {
            const tableBody = document.getElementById('tableBody');
            
            if (tableData.length === 0) {
                tableBody.innerHTML = `
                    <tr>
                        <td colspan="2" class="empty-state">
                            <h3>No Data Available</h3>
                            <p>Waiting for data from Arduino...</p>
                        </td>
                    </tr>
                `;
            } else {
                tableBody.innerHTML = '';
                for (const row of tableData) {
                    const tr = document.createElement('tr');
                    tr.innerHTML = `
                        <td class="attribute">${escapeHtml(row.attribute)}</td>
                        <td class="value">${escapeHtml(row.value)}</td>
                    `;
                    tableBody.appendChild(tr);
                }
            }
        }
        
        // Request table data from Arduino
        function requestTableData() {
            if (!isConnected || socket.readyState !== WebSocket.OPEN) {
                alert('Not connected to Arduino');
                return;
            }
            
            socket.send('TABLE:GET_DATA');
        }
        
        // Escape HTML to prevent XSS
        function escapeHtml(text) {
            const div = document.createElement('div');
            div.textContent = text;
            return div.innerHTML;
        }
        
        // Initialize when page loads
        document.addEventListener('DOMContentLoaded', function() {
            initWebSocket();
            updateConnectionStatus('disconnected');
        });
    </script>
    
    <div class="footer">Created by&nbsp;<a href="https://diyables.io/" target="_blank">DIYables</a></div>
</body>
</html>
)HTMLDELIM";

#endif
