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


## 💡 Usage Tips

1. **Memory Optimization**: Use modular architecture - add only the web apps you need to save memory
2. **WiFi Connection**: Ensure strong WiFi signal for stable WebSocket communication
3. **Pin Safety**: Always check pin capabilities before connecting external devices
4. **Power Supply**: Use adequate power supply for your connected devices
5. **Browser Compatibility**: Works best with modern browsers (Chrome, Firefox, Safari, Edge)
6. **Mobile Friendly**: All interfaces are responsive and work on mobile devices
7. **Start Small**: Begin with 1-2 web apps, then add more features as your project grows


## 📄 License

This library is released under the MIT License. See LICENSE file for details.


Tested Hardware
----------------------------

| Board                   | Tested | Notes                                      |
|-------------------------|:------:|---------------------------------------------|
| Arduino Uno R4 WiFi     |   ✅   | Fully supported       |
| [DIYables STEM V4 IoT](https://diyables.io/products/diyables-stem-v4-iot-fully-compatible-with-arduino-uno-r4-wifi) |   ✅   | Fully supported          |
| [DIYables STEM V4 IoT Starter Kit](https://diyables.io/products/diyables-stem-v4-iot-starter-kit) |   ✅   | Fully supported          |



---

**Happy coding with DIYables WebApps Library!** 🎉
