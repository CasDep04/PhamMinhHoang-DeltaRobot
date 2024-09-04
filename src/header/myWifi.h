#ifndef MYWIFI_H
#define MYWIFI_H

#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
extern String ssid;
extern String password;
extern WebServer server;

void readConfig();
void initWebApp();
void handleClient();

void handleRoot();
void handleNotFound();

void handleSlider();
void handleJoystick();
void handleJoyScript();

#endif