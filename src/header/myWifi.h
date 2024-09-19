#ifndef MYWIFI_H
#define MYWIFI_H

#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
extern String identity;
extern String ssid;
extern String password;
extern WebServer server;

extern int sliderValue;
extern int joystickX;
extern int joystickY;

void readConfig();
void webApp_init();

void readConfigWPA();
void webAppWPA_init();

void handleClient();

void handleRoot();
void handleNotFound();

void handleSlider();
void handleJoystick();
void handleJoyScript();

#endif