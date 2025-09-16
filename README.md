# DIYables WebApps Library

A comprehensive Arduino library for creating WebSocket-based web applications on **Arduino Uno R4 WiFi** and **DIYables STEM V4 IoT**. This library provides multiple ready-to-use web applications for monitoring, controlling, and interacting with your Arduino projects through a modern web interface. **Specially optimized for the DIYables STEM V4 IoT educational platform** with enhanced IoT capabilities and built-in sensors.

## 🚀 Features

- **Modular Architecture**: Add only the web apps you need to optimize memory usage
- **Memory Efficient**: Each web app can be enabled/disabled independently
- **Memory Optimized**: HTML, JavaScript, and CSS codes are minified to reduce code size while preserving UI and functionality. Original unminified source code is included in the library for reference and customization
- **11 Ready-to-Use Web Applications**: Complete Arduino control without web programming knowledge required
  - **Home Page**: Central hub with links to all web applications
  - **Web Monitor**: Real-time serial monitor in your browser via WebSocket
  - **Web Chat**: Interactive chat interface with your Arduino
  - **Web Digital Pins**: Control and monitor all digital pins with web interface
  - **Web Slider**: Dual slider controls for analog/PWM outputs
  - **Web Joystick**: Interactive joystick for robot and vehicle control
  - **Web Analog Gauge**: Circular gauge display for sensor monitoring
  - **Web Rotator**: Rotatable disc control with continuous/limited modes
  - **Web Temperature**: Thermometer visualization with configurable ranges
  - **Web RTC**: Real-time clock with time synchronization and timezone handling
  - **Web Table**: Two-column attribute-value table with real-time updates
  - **Web Plotter**: Real-time data visualization and plotting
- **Custom Web App Template**: Complete template for creating your own web applications with real-time WebSocket communication
- **Responsive Design**: Works on desktop and mobile devices
- **Real-time Communication**: WebSocket-based for instant updates
- **Easy Integration**: Simple callback-based API
- **Multiple App Support**: Support adding multiple web apps at the same time
- **Automatic Home Page Integration**: Added web app is automatically displayed link on the home page
- **Platform Extensible**: Currently implemented for Arduino Uno R4 WiFi, but can be extended for other hardware platforms. See [DIYables_WebApps_ESP32](https://esp32io.com/tutorials/esp32-diyables-web-apps)

## 📦 Installation - Arduino IDE Library Manager
* Open Arduino IDE
* Navigate to the <span class="highlight-text-1">Libraries</span> icon on the left bar of the Arduino IDE.
* Search <span class="quote">"DIYables WebApps"</span>, then find the DIYables WebApps library by DIYables
* Click <span class="highlight-text-1">Install</span> button to install the library.
![Arduino UNO R4 DIYables WebApps library](https://newbiely.com/images/tutorial/arduino-uno-r4-DIYables-WebApps-library.jpg)
* You will be asked for installing some other library dependencies
* Click <span class="highlight-text-1">Install All</span> button to install all library dependencies.
![Arduino UNO R4 DIYables WebApps dependency](https://newbiely.com/images/tutorial/arduino-uno-r4-DIYables-WebApps-dependency-library.jpg)


## 🔧 Dependencies
This library requires the following:
- **UnoR4WiFi_WebServer** library (for WebSocket support)


## 🎯 Quick Start

For detailed setup instructions and code examples, please refer to:
- **[API Reference Documentation](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-library-reference)** - Complete API documentation
- **Example Tutorials** - Comprehensive guides for each web application:
  - **[Web Chat Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-chat)** - Interactive chat interface with Arduino
  - **[Web Monitor Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-monitor)** - Real-time serial monitor via web browser
  - **[Web Plotter Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-plotter)** - Real-time data visualization and plotting
  - **[Web Digital Pins Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-digital-pins)** - Digital pin control and monitoring
  - **[Web Slider Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-slider)** - Dual slider controls for analog/PWM outputs
  - **[Web Joystick Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-joystick)** - Virtual joystick for directional control
  - **[Web Analog Gauge Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-analog-gauge)** - Professional circular gauge for sensor monitoring
  - **[Web Rotator Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-rotator)** - Interactive rotatable disc control for servo/stepper motors
  - **[Web Temperature Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-temperature)** - Visual thermometer display for temperature monitoring
  - **[Web RTC Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-rtc)** - Real-time clock with web-based time synchronization and timezone handling
  - **[Web Table Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-table)** - Two-column data table with real-time attribute-value updates
  - **[CustomWebApp Template](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-custom-webapp)** - Complete template for building your own custom web applications
  - **[Multiple Web Apps Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-multiple-web-apps)** - Complete integration guide combining all features

## 📱 Web Applications

### 1. Home Page (`/`)
- Central navigation hub
- Links to all web applications
- Only enabled/added apps are displayed on the home page
- Connection status display
- Responsive design

### 2. Web Monitor (`/web-monitor`)
- Browser-based serial monitor
- Real-time bidirectional communication
- Message timestamping and counting
- Command input with history

### 3. Web Plotter (`/web-plotter`)
- Real-time data visualization and plotting
- Multiple data series support (up to 8 lines)
- Auto-scaling Y-axis or fixed ranges
- Customizable plot titles and axis labels
- WebSocket streaming for minimal latency
- Perfect for sensor monitoring and debugging

### 4. WebChat (`/chat`)
- Interactive chat interface
- Natural language responses
- LED control via chat commands
- Fun and educational interactions

### 5. Web Digital Pins (`/web-digital-pins`)
- Individual pin control (pins 0-13)
- Each pin can be enabled as INPUT or OUTPUT mode
- Only enabled pins are displayed in the Web UI
- Input and output pin monitoring
- Bulk operations (All ON/OFF, Toggle)
- Real-time pin status feedback

### 6. Web Slider (`/web-slider`)
- Dual range sliders (0-255)
- PWM output control
- Preset value buttons
- Synchronized control options

### 7. Web Joystick (`/web-joystick`)
- Interactive joystick control with touch/mouse support
- X/Y coordinate values (-100 to +100)
- Real-time position feedback
- Auto-center return can be enabled/disabled via Arduino code
- Perfect for robot and vehicle control

### 8. Web Analog Gauge (`/web-gauge`)
- Professional circular gauge display for real-time sensor monitoring
- Configurable value range, units, and precision
- Smooth needle animation with visual feedback
- Color-coded zones (green, yellow, red) for status indication
- Automatic config handling - set range once in constructor
- Perfect for pressure sensors, voltage monitoring, and analog readings

### 9. Web Rotator (`/web-rotator`)
- Interactive rotatable disc control with visual feedback
- Two operation modes: Continuous (0-360°) and Limited (custom range)
- Real-time angle feedback with smooth rotation
- Touch and mouse support for desktop and mobile
- Professional conic gradient design with position indicator
- Perfect for servo motors, stepper motors, and rotational control

### 10. Web Temperature (`/web-temperature`)
- Visual thermometer display with real-time temperature monitoring
- Configurable temperature range and units (°C, °F, K)
- Interactive thermometer visualization with mercury-style animation
- Automatic config handling - set range once in constructor
- Real-time value updates via WebSocket
- Perfect for temperature sensors and environmental monitoring

### 11. Web RTC (`/web-rtc`)
- **Real-time clock display** for both Arduino RTC and client device time
- **One-click time synchronization** from web browser to Arduino RTC
- **Visual time difference indicator** showing sync accuracy in minutes
- **Two-line time format** with 12-hour AM/PM display and full date
- **WebSocket-based real-time updates** for instant time synchronization
- **Modern gradient UI** with responsive card-style layout
- **Timezone-aware synchronization** using local device time
- **Built-in RTC support** specifically for Arduino Uno R4 WiFi
- **Connection status monitoring** with visual WebSocket indicators
- **Automatic time requests** on page load for immediate display
- Perfect for **timestamping, data logging, scheduling, and time-based automation**

### 12. Web Table (`/web-table`)
- **Two-column data table** with attribute-value pairs for organized data display
- **Real-time value updates** via WebSocket for instant data refresh
- **Configurable table structure** set up once in Arduino setup() function
- **Dynamic value updates** during runtime without page refresh
- **Modern responsive design** with hover effects and visual feedback
- **Connection status monitoring** with visual WebSocket indicators
- **Empty state handling** with user-friendly messages when no data available
- **Manual refresh capability** with dedicated refresh button
- **Flexible data types** supporting strings, numbers, and formatted values
- **Memory efficient storage** with configurable maximum rows (default: 20)
- **Automatic data requests** on page load for immediate table population
- Perfect for **sensor monitoring, system status, configuration display, and real-time dashboards**

### 13. CustomWebApp Template (`/custom`)
- **Complete template** for creating your own custom web applications
- **Real-time WebSocket communication** with automatic message filtering
- **Professional class-based design** with encapsulated APP_IDENTIFIER system
- **Beginner-friendly template** with simple text messaging between web and Arduino
- **Auto-reconnect functionality** for reliable WebSocket connections
- **Mobile responsive design** working on phones, tablets, and computers
- **Conflict prevention guidance** for multiple custom apps development
- **Modular file structure** with separated HTML, Arduino logic, and library integration
- **Extensible framework** - modify template to create sophisticated applications
- **Integration ready** - seamlessly works with other DIYables WebApps
- Perfect for **custom IoT interfaces, sensor dashboards, device control panels, and educational projects**

## 🧩 Modular Architecture

**Memory Optimization**: The DIYables WebApps library features a modular design that allows you to include only the web applications you actually need, significantly reducing memory usage on your Arduino.

### Key Benefits:
- **Selective Integration**: Add only required web apps to your project
- **Memory Efficient**: Each web app is independent and optional
- **Scalable**: Start small and add more features as needed
- **Performance Optimized**: Fewer active apps = better performance

### How It Works:
```cpp
// Basic setup - include only what you need
DIYablesWebAppServer webAppsServer(80, 81);
DIYablesHomePage homePage;                              // Always recommended
DIYablesWebSliderPage webSliderPage;                    // Only if you need sliders
DIYablesWebJoystickPage webJoystickPage;                // Only if you need joystick
DIYablesWebAnalogGaugePage gaugePage(0.0, 100.0, "V"); // Only if you need analog gauge
DIYablesWebRotatorPage webRotatorPage(ROTATOR_MODE_CONTINUOUS);  // Only if you need rotator
DIYablesWebTemperaturePage tempPage(-10.0, 50.0, "°C"); // Only if you need temperature
DIYablesWebRTCPage webRTCPage;                          // Only if you need time sync

// Add only the apps you want
webAppsServer.addApp(&homePage);
webAppsServer.addApp(&webSliderPage);    // Skip apps you don't need
webAppsServer.addApp(&gaugePage);        // Add only what you use
webAppsServer.addApp(&tempPage);         // to save memory
webAppsServer.addApp(&webRotatorPage);   // Customize as needed
webAppsServer.addApp(&webRTCPage);       // Add time synchronization

// Runtime management (advanced)
if (sensorConnected) {
  webAppsServer.addApp(&webJoystickPage);  // Add dynamically
}
```


### Runtime Flexibility:
- **Dynamic Management**: Add or remove apps during runtime using `addApp()` and `removeApp()`
- **Conditional Loading**: Load apps based on hardware or configuration
- **Custom Apps**: Create custom web applications by inheriting from `DIYablesWebAppPageBase`
- **No Recompilation**: Change available apps without rebuilding

## 🔌 API Reference

For complete API documentation including all classes, methods, and usage examples, see:
**[API Reference Documentation](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-library-reference)**

## 📋 Examples

The library includes comprehensive example tutorials:

- **[Web Chat Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-chat)** - Interactive chat interface with Arduino
- **[Web Monitor Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-monitor)** - Real-time serial monitor via web browser
- **[Web Plotter Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-plotter)** - Real-time data visualization and plotting
- **[Web Digital Pins Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-digital-pins)** - Digital pin control and monitoring
- **[Web Slider Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-slider)** - Dual slider controls for analog/PWM outputs
- **[Web Joystick Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-joystick)** - Virtual joystick for directional control
- **[Web Analog Gauge Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-analog-gauge)** - Professional circular gauge for sensor monitoring
- **[Web Rotator Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-rotator)** - Interactive rotatable disc control for servo/stepper motors
- **[Web Temperature Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-temperature)** - Visual thermometer display for temperature monitoring
- **[Web RTC Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-rtc)** - Real-time clock with web-based time synchronization and timezone handling
- **[Web Table Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-web-table)** - Two-column data table with real-time attribute-value updates
- **[CustomWebApp Template](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-custom-webapp)** - Complete template for building your own custom web applications
- **[Multiple Web Apps Example](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-multiple-web-apps)** - Complete integration guide combining all features

Each example tutorial includes:
- Step-by-step setup instructions
- Hardware connection diagrams
- Complete code examples
- Troubleshooting guides
- Project ideas and integration tips

## 🌐 Web Interface URLs

Once connected to WiFi, access the applications at:

- **Home**: `http://[IP_ADDRESS]/`
- **Web Chat**: `http://[IP_ADDRESS]/chat`
- **Web Monitor**: `http://[IP_ADDRESS]/web-monitor`
- **Web Plotter**: `http://[IP_ADDRESS]/web-plotter`
- **Web Digital Pins**: `http://[IP_ADDRESS]/web-digital-pins`
- **Web Slider**: `http://[IP_ADDRESS]/web-slider`
- **Web Joystick**: `http://[IP_ADDRESS]/web-joystick`
- **Web Analog Gauge**: `http://[IP_ADDRESS]/web-gauge`
- **Web Rotator**: `http://[IP_ADDRESS]/web-rotator`
- **Web Temperature**: `http://[IP_ADDRESS]/web-temperature`
- **Web RTC**: `http://[IP_ADDRESS]/web-rtc`
- **Web Table**: `http://[IP_ADDRESS]/web-table`
- **Custom App**: `http://[IP_ADDRESS]/custom` (when using CustomWebApp template)

## 🔧 Hardware Setup

### DIYables STEM V4 IoT (Recommended Platform)
- **Built-in WiFi capability** with optimized antenna design
- **Onboard LEDs and sensors** ready to use out of the box
- **Extended I/O options** with additional connectivity
- **Educational-focused design** perfect for learning IoT development
- **Professional-grade components** for reliable prototyping
- **Comprehensive pin layout** optimized for breadboard use
- **Enhanced power management** for stable operation
- **Perfect for STEM education** and IoT project development

### Arduino Uno R4 WiFi
- No additional hardware required for basic functionality
- Connect LEDs to digital pins for visual feedback
- Connect sensors to analog pins for monitoring
- Standard Arduino compatibility

## 💡 Usage Tips

1. **Memory Optimization**: Use modular architecture - add only the web apps you need to save memory
2. **WiFi Connection**: Ensure strong WiFi signal for stable WebSocket communication
3. **Pin Safety**: Always check pin capabilities before connecting external devices
4. **Power Supply**: Use adequate power supply for your connected devices
5. **Browser Compatibility**: Works best with modern browsers (Chrome, Firefox, Safari, Edge)
6. **Mobile Friendly**: All interfaces are responsive and work on mobile devices
7. **Start Small**: Begin with 1-2 web apps, then add more features as your project grows

## 🔍 Troubleshooting

### WiFi Connection Issues
- Verify SSID and password
- Check WiFi signal strength
- Ensure 2.4GHz network (5GHz not supported)

### WebSocket Connection Problems
- Check firewall settings
- Verify IP address in browser
- Try refreshing the web page
- Check Serial Monitor for error messages

### Performance Issues
- **Memory Optimization**: Remove unused web apps to free up RAM and Flash memory
- **Selective Loading**: Use modular architecture to include only needed functionality
- Limit update frequency for high-frequency data
- Use appropriate delays in loop()
- Monitor memory usage for long-running applications

## 📚 Advanced Usage

### Dynamic App Management
The library supports runtime addition and removal of web applications:

```cpp
// Add apps dynamically during runtime
if (sensorConnected && !webAppsServer.getApp("/webmonitor")) {
    webAppsServer.addApp(new DIYablesWebMonitorPage());
}

// Remove apps to free memory
webAppsServer.removeApp("/chat");  // Remove webchat if not needed

// Get specific app instances
DIYablesWebDigitalPinsPage* pinsPage = webAppsServer.getWebDigitalPinsPage();
if (pinsPage) {
    pinsPage->enablePin(2, WEB_PIN_OUTPUT);
}
```

### Custom Web Applications
Create your own web apps by inheriting from `DIYablesWebAppPageBase`:

```cpp
class MySensorDashboard : public DIYablesWebAppPageBase {
public:
    MySensorDashboard() : DIYablesWebAppPageBase("/sensors") {}
    
    void handleHTTPRequest(WiFiClient& client) override {
        sendHTTPHeader(client);
        client.print("<h1>Sensor Dashboard</h1>");
        client.print("<p>Temperature: " + String(getTemperature()) + "°C</p>");
    }
    
    void handleWebSocketMessage(WebSocket& ws, const String& message) override {
        if (message == "get_data") {
            sendWebSocketMessage(ws, "temp:" + String(getTemperature()));
        }
    }
};

// Add your custom app
webAppsServer.addApp(new MySensorDashboard());
```

### Custom HTML Pages
You can modify the HTML files in the `src/html/` directory to customize the web interface appearance and functionality.

### Multiple WebSocket Clients
The library supports multiple simultaneous WebSocket connections, allowing multiple users to control the same Arduino.

### Integration with Other Libraries
Easily integrate with sensor libraries, servo control, motor drivers, and other Arduino libraries.


## 📄 License

This library is released under the MIT License. See LICENSE file for details.

## 🔗 Links

- **[API Reference Documentation](https://newbiely.com/tutorials/arduino-uno-r4/diyables-web-apps-library-reference)** - Complete API documentation
- **[Tutorial](https://newbiely.com/tutorials/arduino-uno-r4/arduino-uno-r4-diyables-webapps)** - Step-by-step tutorial
- **[DIYables STEM V4 IoT](https://diyables.io/products/diyables-stem-v4-iot-fully-compatible-with-arduino-uno-r4-wifi)** - Get the recommended development board
- **[DIYables Products](https://diyables.io)** - Explore our complete IoT and STEM education lineup
- **Arduino Uno R4 WiFi**: [Arduino Official Page](https://arduino.cc)


---

**Happy coding with DIYables WebApps Library!** 🎉
