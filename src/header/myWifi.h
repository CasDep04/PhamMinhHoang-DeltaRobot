#ifndef MYWIFI_H
#define MYWIFI_H

#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
extern const char* ssid;
extern const char* password;
extern WebServer server;

void initWebApp();
void handleClient();
void handleRoot();
void handleNotFound();


#endif