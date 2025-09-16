#ifndef DIYABLES_WEB_PLOTTER_PAGE_H
#define DIYABLES_WEB_PLOTTER_PAGE_H

#include "DIYablesWebAppPageBase.h"

// Callback function pointers specific to WebPlotter
extern void (*webPlotterDataCallback)();
extern void (*webPlotterConfigCallback)();

/**
 * WebPlotter page handler - manages real-time data plotting interface
 */
class DIYablesWebPlotterPage : public DIYablesWebAppPageBase {
public:
    DIYablesWebPlotterPage();
    
    // Inherited virtual methods
    void handleHTTPRequest(IWebClient& client) override;
    void handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) override;
    const char* getPageInfo() const override;
    String getNavigationInfo() const override;
    
    // Callback setters
    void onPlotterDataRequest(void (*callback)());
    
    // Send methods for plotting data
    void sendPlotData(float value);
    void sendPlotData(float value1, float value2);
    void sendPlotData(float value1, float value2, float value3);
    void sendPlotData(float value1, float value2, float value3, float value4);
    void sendPlotData(float values[], int count);
    void sendPlotData(const String& dataLine);
    
    // Configuration methods
    void setPlotTitle(const String& title);
    void setAxisLabels(const String& xLabel, const String& yLabel);
    void setYAxisRange(float minY, float maxY);
    void enableAutoScale(bool enable = true);
    void setMaxSamples(int maxSamples);
    
private:
    String plotTitle;
    String xAxisLabel;
    String yAxisLabel;
    float yAxisMin;
    float yAxisMax;
    bool autoScale;
    int maxSamples;
};

#endif
