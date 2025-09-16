#include "DIYablesWebPlotterPage.h"
#include "html/web_plotter.h"
#include <string.h>

// Callback function pointers specific to WebPlotter
void (*webPlotterDataCallback)() = nullptr;

DIYablesWebPlotterPage::DIYablesWebPlotterPage() : DIYablesWebAppPageBase("/web-plotter") {
    plotTitle = "Arduino - Web Plotter";
    xAxisLabel = "Samples";
    yAxisLabel = "Values";
    yAxisMin = -5.0;
    yAxisMax = 5.0;
    autoScale = true;
    maxSamples = 50;
}

void DIYablesWebPlotterPage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_PLOTTER_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebPlotterPage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for web plotter (with PLOTTER: prefix)
    if (strncmp(message, "PLOTTER:", 8) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebPlotter WebSocket received: ");
    Serial.println(message);
    
    // Handle different plotter commands
    if (strcmp(message, "PLOTTER:REQUEST_DATA") == 0) {
        if (webPlotterDataCallback) {
            webPlotterDataCallback();
        }
    } else if (strcmp(message, "PLOTTER:GET_CONFIG") == 0) {
        // Send current configuration using fixed buffer to avoid memory fragmentation
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "PLOTTER_CONFIG:%s|%s|%s|%.1f|%.1f|%d|%d",
                 plotTitle.c_str(), xAxisLabel.c_str(), yAxisLabel.c_str(),
                 yAxisMin, yAxisMax, autoScale ? 1 : 0, maxSamples);
        broadcastToAllClients(buffer);
    }
}

void DIYablesWebPlotterPage::onPlotterDataRequest(void (*callback)()) {
    webPlotterDataCallback = callback;
}

void DIYablesWebPlotterPage::sendPlotData(float value) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "PLOTTER_DATA:%.2f", value);
    broadcastToAllClients(buffer);
}

void DIYablesWebPlotterPage::sendPlotData(float value1, float value2) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "PLOTTER_DATA:%.2f %.2f", value1, value2);
    broadcastToAllClients(buffer);
}

void DIYablesWebPlotterPage::sendPlotData(float value1, float value2, float value3) {
    char buffer[96];
    snprintf(buffer, sizeof(buffer), "PLOTTER_DATA:%.2f %.2f %.2f", value1, value2, value3);
    broadcastToAllClients(buffer);
}

void DIYablesWebPlotterPage::sendPlotData(float value1, float value2, float value3, float value4) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "PLOTTER_DATA:%.2f %.2f %.2f %.2f", value1, value2, value3, value4);
    broadcastToAllClients(buffer);
}

void DIYablesWebPlotterPage::sendPlotData(float values[], int count) {
    // Limit count to prevent buffer overflow
    if (count > 8) count = 8;  // Max 8 data series
    
    char buffer[256];  // Large enough for 8 values
    strcpy(buffer, "PLOTTER_DATA:");
    
    for (int i = 0; i < count; i++) {
        char valueStr[16];
        snprintf(valueStr, sizeof(valueStr), "%.2f", values[i]);
        
        if (i > 0) strcat(buffer, " ");
        strcat(buffer, valueStr);
    }
    
    broadcastToAllClients(buffer);
}

void DIYablesWebPlotterPage::sendPlotData(const String& dataLine) {
    // Prevent memory issues with very long data lines
    if (dataLine.length() > 200) {
        Serial.println("WARNING: Data line too long, truncating");
        String truncated = dataLine.substring(0, 200);
        String message = "PLOTTER_DATA:" + truncated;
        broadcastToAllClients(message.c_str());
    } else {
        String message = "PLOTTER_DATA:" + dataLine;
        broadcastToAllClients(message.c_str());
    }
}

void DIYablesWebPlotterPage::setPlotTitle(const String& title) {
    plotTitle = title;
}

void DIYablesWebPlotterPage::setAxisLabels(const String& xLabel, const String& yLabel) {
    xAxisLabel = xLabel;
    yAxisLabel = yLabel;
}

void DIYablesWebPlotterPage::setYAxisRange(float minY, float maxY) {
    yAxisMin = minY;
    yAxisMax = maxY;
    autoScale = false;
}

void DIYablesWebPlotterPage::enableAutoScale(bool enable) {
    autoScale = enable;
}

void DIYablesWebPlotterPage::setMaxSamples(int samples) {
    maxSamples = samples;
}

const char* DIYablesWebPlotterPage::getPageInfo() const {
    return "📊 Web Plotter";
}

String DIYablesWebPlotterPage::getNavigationInfo() const {
    return "<a href=\"/web-plotter\" class=\"app-card plotter\" style=\"background: linear-gradient(135deg, #ffecd2 0%, #fcb69f 100%); color: #333;\">"
           "<h3>📊 Web Plotter</h3>"
           "<p>Real-time data visualization and plotting</p>"
           "</a>";
}
