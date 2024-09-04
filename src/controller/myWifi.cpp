#include "./header/myWifi.h"
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "";
const char* password = "";
WebServer server(80);

void initWebApp() {
    // Connect to Wi-Fi
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("Connecting...\n");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Set up server routes
    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);

    // Start the server
    server.begin();
    Serial.println("Server started");
}

void handleClient() {
    server.handleClient();
}

void handleRoot() {
    server.send(200, "text/html", "<h1>Hello from ESP32 Web Server</h1>");
}

void handleNotFound() {
    server.send(404, "text/plain", "404: Not Found");
}


