#include "./header/myWifi.h"
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "pmh";
const char* password = "0908161221";
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
    String html = "<!DOCTYPE html><html><head><title>ESP32 Control</title>";
    html += "<style>";
    html += "body { font-family: Arial; text-align: center; margin-top: 50px; }";
    html += ".slider-container { width: 80%; margin: auto; }";
    html += "#joystick-container { width: 80%; margin: auto; }";
    html += ".slider { width: 100%; }";
    html += "#joystick { height: 200px; width: 200px; background-color: lightgray; border-radius: 50%; position: relative; }";
    html += "#knob { height: 50px; width: 50px; background-color: darkgray; border-radius: 50%; position: absolute; top: 75px; left: 75px; }";
    html += "</style>";
    html += "</head><body>";

    html += "<h1>ESP32 Slider and Joystick Control</h1>";

    // Slider
    html += "<div class='slider-container'>";
    html += "<label for='slider'>Slider Value:</label>";
    html += "<input type='range' min='0' max='100' value='50' class='slider' id='slider'>";
    html += "<p>Value: <span id='sliderValue'>50</span></p>";
    html += "</div>";

    // Joystick
    html += "<div id='joystick-container'>";
    html += "<div id='joystick'><div id='knob'></div></div>";
    html += "<p>Joystick X: <span id='joystickX'>0</span> Y: <span id='joystickY'>0</span></p>";
    html += "</div>";

    // JavaScript for Slider and Joystick
    html += "<script>";
    // Slider logic
    html += "var slider = document.getElementById('slider');";
    html += "var sliderValue = document.getElementById('sliderValue');";
    html += "slider.oninput = function() { sliderValue.innerHTML = this.value; sendSliderValue(this.value); };";
    html += "function sendSliderValue(value) { fetch('/slider?value=' + value); }";

    // Joystick logic
    html += "var knob = document.getElementById('knob');";
    html += "var joystickX = document.getElementById('joystickX');";
    html += "var joystickY = document.getElementById('joystickY');";
    html += "var joystickContainer = document.getElementById('joystick');";
    html += "var dragging = false;";
    html += "joystickContainer.addEventListener('mousedown', function(event) { dragging = true; });";
    html += "document.addEventListener('mouseup', function() { dragging = false; });";
    html += "document.addEventListener('mousemove', function(event) {";
    html += "if (dragging) {";
    html += "var rect = joystickContainer.getBoundingClientRect();";
    html += "var x = event.clientX - rect.left - knob.offsetWidth / 2;";
    html += "var y = event.clientY - rect.top - knob.offsetHeight / 2;";
    html += "x = Math.max(0, Math.min(x, joystickContainer.offsetWidth - knob.offsetWidth));";
    html += "y = Math.max(0, Math.min(y, joystickContainer.offsetHeight - knob.offsetHeight));";
    html += "knob.style.left = x + 'px';";
    html += "knob.style.top = y + 'px';";
    html += "joystickX.innerHTML = x;";
    html += "joystickY.innerHTML = y;";
    html += "sendJoystickValues(x, y);";
    html += "}});";
    html += "function sendJoystickValues(x, y) { fetch('/joystick?x=' + x + '&y=' + y); }";
    html += "</script>";

    html += "</body></html>";

    server.send(200, "text/html", html);
}


void handleNotFound() {
    server.send(404, "text/plain", "404: Not Found");
}


