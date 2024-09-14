#include "myWifi.h"
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include <esp_wpa2.h>

String identity;
String ssid;
String password;
WebServer server(80);

int sliderValue = 0;  // Default value for the slider

int joystickX = 0;
int joystickY = 0;

void readConfig()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    File file = SPIFFS.open("/config.txt", "r");
    if (!file)
    {
        Serial.println("Failed to open config file");
        return;
    }

    while (file.available())
    {
        String line = file.readStringUntil('\n');
        line.trim(); // Remove any whitespace/newline characters
        if (line.startsWith("SSID="))
        {
            ssid = line.substring(5);
        }
        else if (line.startsWith("PASSWORD="))
        {
            password = line.substring(9);
        }
    }

    file.close();
}

void webApp_init() {
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
    server.on("/joystick", handleJoystick);  // Handle joystick values
    server.on("/slider", handleSlider);  // Handle slider values
    server.on("/joy.js", HTTP_GET, handleJoyScript);  // Serve the joystick JavaScript file

    server.onNotFound(handleNotFound);

    // Start the server
    server.begin();
    Serial.println("Server started");
}

void readConfigWPA() {
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    File file = SPIFFS.open("/configWPA.txt", "r");
    if (!file) {
        Serial.println("Failed to open WPA config file");
        return;
    }

    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim();  // Remove any whitespace/newline characters
        if (line.startsWith("SSID=")) {
            ssid = line.substring(5);
        } else if (line.startsWith("IDENTITY=")) {
            identity = line.substring(9);
        } else if (line.startsWith("PASSWORD=")) {
            password = line.substring(9);
        }
    }

    file.close();
}

void webAppWPA_init() {
    readConfigWPA();

    if (ssid.isEmpty() || password.isEmpty() || identity.isEmpty()) {
        Serial.println("SSID, Identity, or Password not set in WPA config file");
        return;
    }

    // WPA2-Enterprise settings
    WiFi.disconnect(true);  // Disconnect before setting up WPA2-Enterprise

    // Set WPA2-Enterprise credentials
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)identity.c_str(), identity.length());
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)identity.c_str(), identity.length());
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password.c_str(), password.length());
    esp_wifi_sta_wpa2_ent_enable();  // Enable WPA2-Enterprise mode

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid.c_str());

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("Connecting...\n");
    }

    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Set up server routes
    server.on("/", handleRoot);
    server.on("/joystick", handleJoystick);  // Handle joystick values
    server.on("/slider", handleSlider);  // Handle slider values
    server.on("/joy.js", HTTP_GET, handleJoyScript);  // Serve the joystick JavaScript file

    server.onNotFound(handleNotFound);

    // Start the server
    server.begin();
    Serial.println("Server started");
}


void handleClient()
{
    server.handleClient();
}

void handleRoot() {
    String html = "<!DOCTYPE html><html><head><title>ESP32 Control</title></head>";
    html += "<style>";
    html += "body { font-family: Arial; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }";
    html += ".container { display: flex; flex-direction: column; align-items: center; text-align: center; width: 100%; }";
    html += ".header { font-size: 24px; margin-bottom: 40px; }";  // Header styling
    html += ".joystick-container { margin-bottom: 20px; }";  // Space between joystick and slider
    html += ".slider-container { margin-top: 20px; width: 50%; display: flex; flex-direction: column; align-items: center; }";  // Center slider
    html += "</style>";
    html += "<script src=\"/joy.js\"></script>";  // Load the joystick JavaScript file
    html += "</head><body>";
    html += "<div class='container'>";
    html += "<div class='header'>ESP32 Controls</div>";  // ESP32 Controls header
    html += "<div class='slider-container'>";
    html += "<p>Adjustable Slider</p>";
    html += "<input type='range' min='0' max='100' value='50' id='slider' oninput='updateSliderValue(this.value)'/>";
    html += "<p>Slider Value: <span id='sliderValue'>50</span></p>";
    html += "</div>";
    html += "<div class='joystick-container'>";
    html += "<div id='joy1Div' style='width:200px;height:200px;margin:50px'></div>";
    html += "<p>Joystick X: <input id='joyX' type='text' /></p>";
    html += "<p>Joystick Y: <input id='joyY' type='text' /></p>";
    html += "</div>";
    html += "</div>";
    html += "<script>";
    // Joystick JavaScript
    html += "var joyX = document.getElementById('joyX');";
    html += "var joyY = document.getElementById('joyY');";
    html += "var Joy1 = new JoyStick('joy1Div', {}, function(stickData) {";
    html += "joyX.value = stickData.x;";
    html += "joyY.value = stickData.y;";
    html += "fetch('/joystick?x=' + stickData.x + '&y=' + stickData.y);";  // Send joystick data to ESP32
    html += "});";
    // Slider JavaScript
    html += "function updateSliderValue(value) {";
    html += "  document.getElementById('sliderValue').innerText = value;";
    html += "  fetch('/slider?value=' + value);";  // Send slider value to ESP32
    html += "}";
    html += "</script>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}


void handleNotFound()
{
    server.send(404, "text/plain", "404: Not Found");
}

void handleJoystick() {
    if (server.hasArg("x") && server.hasArg("y")) {
        joystickX = server.arg("x").toInt();  // Update the X variable
        joystickY = server.arg("y").toInt();  // Update the Y variable
        Serial.print("Joystick X: ");
        Serial.print(joystickX);
        Serial.print(" | Joystick Y: ");
        Serial.println(joystickY);
    }
    server.send(200, "text/plain", "Joystick values updated");

    
}

void handleSlider() {
    if (server.hasArg("value")) {
        sliderValue = server.arg("value").toInt();  // Update slider value
        Serial.print("Slider Value: ");
        Serial.println(sliderValue);
    }
    server.send(200, "text/plain", "Slider value updated");
}

void handleJoyScript() {
    // Open the 'joy.js' file stored in SPIFFS
    File file = SPIFFS.open("/joy.js", "r");
    if (!file) {
        // If the file doesn't exist, send a 404 error
        server.send(404, "text/plain", "File not found");
        return;
    }
    // Stream the file content to the client with the correct MIME type
    server.streamFile(file, "application/javascript");
    file.close();  // Close the file after serving it
}