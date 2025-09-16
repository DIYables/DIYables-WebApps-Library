#ifndef HOME_PAGE_START_HTML_H
#define HOME_PAGE_START_HTML_H

const char HOME_PAGE_START_HTML[] PROGMEM = R"HTMLDELIM(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>DIYables WebApp - Home</title>
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
            padding: 0;
        }
        
        .container {
            background: white;
            border-radius: 0;
            box-shadow: none;
            padding: 40px;
            width: 100%;
            min-height: 100vh;
            max-width: 1200px;
            margin: 0 auto;
            display: flex;
            flex-direction: column;
            justify-content: flex-start;
        }
        
        .header {
            text-align: center;
            margin-top: 20px;
            margin-bottom: 40px;
        }
        
        .header h1 {
            color: #333;
            font-size: 2.5em;
            margin-bottom: 10px;
        }
        
        .header p {
            color: #666;
            font-size: 1.2em;
        }
        
        .apps-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 20px;
            margin-bottom: 40px;
        }
        
        .app-card {
            background: #f8f9fa;
            border: 2px solid #e9ecef;
            border-radius: 12px;
            padding: 24px;
            text-decoration: none;
            color: inherit;
            transition: all 0.3s ease;
            position: relative;
            overflow: hidden;
        }
        
        .app-card:hover {
            transform: translateY(-4px);
            box-shadow: 0 8px 25px rgba(0,0,0,0.1);
            border-color: #007bff;
        }
        
        .app-card h3 {
            color: #333;
            margin-bottom: 8px;
            font-size: 1.3em;
        }
        
        .app-card p {
            color: #666;
            line-height: 1.5;
            margin: 0;
        }
        
        .app-card.monitor {
            border-left: 4px solid #17a2b8;
        }
        
        .app-card.chat {
            border-left: 4px solid #28a745;
        }
        
        .app-card.control {
            border-left: 4px solid #007bff;
        }
        
        .app-card.slider {
            border-left: 4px solid #ffc107;
        }
        
        .app-card.joystick {
            border-left: 4px solid #6f42c1;
        }
        
        .app-card.custom {
            border-left: 4px solid #fd7e14;
        }
        
        .status {
            background: #f8f9fa;
            border: 1px solid #dee2e6;
            border-radius: 8px;
            padding: 20px;
            margin-top: auto;
        }
        
        .status h4 {
            color: #333;
            margin-bottom: 15px;
            font-size: 1.1em;
        }
        
        .status-info {
            display: flex;
            flex-wrap: wrap;
            gap: 20px;
        }
        
        .status-item {
            flex: 1;
            min-width: 120px;
        }
        
        .status-item strong {
            color: #495057;
            display: block;
            margin-bottom: 5px;
        }
        
        .status-item span {
            color: #007bff;
            font-weight: 600;
        }
        
        .footer {
            text-align: center;
            margin-top: 30px;
            padding-top: 20px;
            border-top: 1px solid #dee2e6;
            color: #6c757d;
            font-size: 0.9em;
        }
        
        .no-apps {
            text-align: center;
            color: #6c757d;
            font-style: italic;
            padding: 40px;
            background: #f8f9fa;
            border-radius: 8px;
            margin-bottom: 40px;
        }
        
        @media (max-width: 768px) {
            .container {
                padding: 20px;
            }
            
            .header h1 {
                font-size: 2em;
            }
            
            .header p {
                font-size: 1em;
            }
            
            .apps-grid {
                grid-template-columns: 1fr;
                gap: 15px;
            }
            
            .app-card {
                padding: 20px;
            }
            
            .status-info {
                flex-direction: column;
                gap: 10px;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>🚀 DIYables WebApp</h1>
            <p>Arduino Uno R4 WiFi & DIYables STEM V4 IoT Web Applications</p>
        </div>
        
        <div class="apps-grid">
)HTMLDELIM";

#endif
