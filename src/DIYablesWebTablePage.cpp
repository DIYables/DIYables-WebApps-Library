#include "DIYablesWebTablePage.h"
#include "html/web_table.h"
#include <string.h>

// Callback function pointer specific to WebTable
void (*webTableValueRequestCallback)() = nullptr;

DIYablesWebTablePage::DIYablesWebTablePage() : DIYablesWebAppPageBase("/web-table") {
    rowCount = 0;
    // Initialize attributes array
    for(int i = 0; i < MAX_TABLE_ROWS; i++) {
        attributes[i] = "";
    }
}

void DIYablesWebTablePage::handleHTTPRequest(IWebClient& client) {
    sendHTTPHeader(client);
    sendLargeHTML(client, WEB_TABLE_HTML);  // Use chunked sending for large HTML
}

void DIYablesWebTablePage::handleWebSocketMessage(IWebSocket& ws, const char* message, uint16_t length) {
    // Only handle messages intended for web table (with TABLE: prefix)
    if (strncmp(message, "TABLE:", 6) != 0) {
        // Ignore messages from other pages
        return;
    }
    
    Serial.print("WebTable WebSocket received: ");
    Serial.println(message);
    
    // Handle request for table configuration first
    if (strcmp(message, "TABLE:GET_CONFIG") == 0) {
        // Send table structure configuration
        char config[512];
        strcpy(config, "TABLE_CONFIG:[");
        for (int i = 0; i < rowCount; i++) {
            if (i > 0) strcat(config, ",");
            strcat(config, "\"");
            strcat(config, attributes[i].c_str());
            strcat(config, "\"");
        }
        strcat(config, "]");
        sendToWebTable(config);
        return;
    }
    
    // Handle request for table data
    if (strcmp(message, "TABLE:GET_DATA") == 0) {
        if (webTableValueRequestCallback) {
            webTableValueRequestCallback();
        }
        return;
    }
    
    // Handle value update requests
    if (strncmp(message, "TABLE:UPDATE:", 13) == 0) {
        const char* updateData = message + 13; // Skip "TABLE:UPDATE:"
        const char* colonPos = strchr(updateData, ':');
        if (colonPos != nullptr) {
            // Extract attribute name
            int attrLen = colonPos - updateData;
            char attribute[64];
            if (attrLen < sizeof(attribute)) {
                strncpy(attribute, updateData, attrLen);
                attribute[attrLen] = '\0';
                
                // Extract value
                const char* value = colonPos + 1;
                
                // Since we don't store values, just broadcast the update to all clients
                char broadcastMsg[256];
                snprintf(broadcastMsg, sizeof(broadcastMsg), "VALUE_UPDATE:%s:%s", attribute, value);
                sendToWebTable(broadcastMsg);
            }
        }
        return;
    }
}

const char* DIYablesWebTablePage::getPageInfo() const {
    return "📊 Web Table";
}

String DIYablesWebTablePage::getNavigationInfo() const {
    return "<a href=\"/web-table\" class=\"app-card table\" style=\"background: linear-gradient(135deg, #9C27B0 0%, #673AB7 100%); color: #fff;\">"
           "<h3 style=\"color: #fff;\">📊 Web Table</h3>"
           "<p style=\"color: #fff;\">Display real-time data in organized table format</p>"
           "</a>";
}

void DIYablesWebTablePage::addRow(const String& attribute) {
    if (rowCount < MAX_TABLE_ROWS) {
        attributes[rowCount] = attribute;
        rowCount++;
    }
}

void DIYablesWebTablePage::clearTable() {
    rowCount = 0;
    for(int i = 0; i < MAX_TABLE_ROWS; i++) {
        attributes[i] = "";
    }
}

int DIYablesWebTablePage::getRowCount() const {
    return rowCount;
}

String DIYablesWebTablePage::getAttribute(int index) const {
    if (index >= 0 && index < rowCount) {
        return attributes[index];
    }
    return "";
}

void DIYablesWebTablePage::onTableValueRequest(void (*callback)()) {
    webTableValueRequestCallback = callback;
}

void DIYablesWebTablePage::sendToWebTable(const char* message) {
    // Send to all connected clients
    broadcastToAllClients(message);
}

void DIYablesWebTablePage::sendToWebTable(const String& message) {
    // FIXED: Direct broadcast to avoid additional String operations
    broadcastToAllClients(message.c_str());
}

void DIYablesWebTablePage::sendValueUpdate(const String& attribute, const String& value) {
    // FIXED: Use char array instead of String concatenation to prevent WebSocket frame corruption
    char message[256];
    snprintf(message, sizeof(message), "VALUE_UPDATE:%s:%s", attribute.c_str(), value.c_str());
    broadcastToAllClients(message);
}

void DIYablesWebTablePage::sendValueUpdate(int index, const String& value) {
    if (index >= 0 && index < rowCount) {
        sendValueUpdate(attributes[index], value);
    }
}
