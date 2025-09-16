#ifndef NOT_FOUND_HTML_H
#define NOT_FOUND_HTML_H

const char NOT_FOUND_HTML[] PROGMEM = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Web App Not Available</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <meta charset='UTF-8'>
    <link rel="icon" href="https://diyables.io/images/page/diyables.svg">
    <style>
        body { 
            font-family: -webkit-system-font, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Arial, sans-serif; 
            margin: 40px; 
            background: #f5f5f5; 
            text-align: center; 
            line-height: 1.4;
        }
        .container { 
            max-width: 500px; 
            margin: 0 auto; 
            background: white; 
            padding: 30px; 
            border-radius: 10px; 
            box-shadow: 0 4px 15px rgba(0,0,0,0.1); 
        }
        h1 { 
            color: #e74c3c; 
            margin-bottom: 10px; 
        }
        h2 { 
            color: #2c3e50; 
            margin-top: 25px; 
            margin-bottom: 15px; 
        }
        p { 
            color: #555; 
            line-height: 1.6; 
            margin-bottom: 20px; 
        }
        .btn { 
            display: inline-block; 
            background: #3498db; 
            color: white; 
            padding: 12px 20px; 
            text-decoration: none; 
            border-radius: 6px; 
            margin: 8px; 
            font-weight: bold; 
        }
        .btn:hover { 
            background: #2980b9; 
        }
        .home-btn { 
            background: #27ae60; 
        }
        .home-btn:hover { 
            background: #229954; 
        }
        .footer {
            font-size: 12px; 
            color: #888; 
            margin-top: 30px;
        }
    </style>
</head>
<body>
    <div class='container'>
        <h1>&#x26D4; Page Not Available</h1>
        <p>The requested web application is not found or has not been added on this Arduino device. Add applications using server.addApp() to see them here</p>
        
        <h2>Quick Actions</h2>
        <div>
            <a href='/' class='btn home-btn'>&#x1F3E0; Go to Home Page</a>
            <a href='https://diyables.io/webapps-r4' target='_blank' class='btn'>&#x1F4DA; View Tutorials</a>
        </div>
        
        <p class='footer'>&#x1F4A1; Powered by DIYables WebApps Library</p>
    </div>
</body>
</html>
)";

#endif
