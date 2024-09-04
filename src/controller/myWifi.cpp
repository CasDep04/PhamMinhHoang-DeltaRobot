#include "./header/myWifi.h"
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

String ssid ;
String password ;
WebServer server(80);

void readConfig() {
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    File file = SPIFFS.open("/config.txt", "r");
    if (!file) {
        Serial.println("Failed to open config file");
        return;
    }

    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim(); // Remove any whitespace/newline characters
        if (line.startsWith("SSID=")) {
            ssid = line.substring(5);
        } else if (line.startsWith("PASSWORD=")) {
            password = line.substring(9);
        }
    }

    file.close();
}

void initWebApp() {
    readConfig();

    if (ssid.isEmpty() || password.isEmpty()) {
        Serial.println("SSID or Password not set in config file");
        return;
    }

    // Connect to Wi-Fi
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid.c_str(), password.c_str());

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
    server.on("/slider", []() {
        String sliderValue = server.arg("value");
        Serial.print("Slider Value: ");
        Serial.println(sliderValue);
        server.send(200, "text/plain", "Slider value received");
    });
    
    server.on("/joystick", []() {
        String xValue = server.arg("x");
        String yValue = server.arg("y");
        Serial.print("Joystick X: ");
        Serial.print(xValue);
        Serial.print(" Y: ");
        Serial.println(yValue);
        server.send(200, "text/plain", "Joystick values received");
    });

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


