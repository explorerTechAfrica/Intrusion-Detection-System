#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeWiFi();

/*******************************************************
 * CONNECTION
 *******************************************************/
bool connectWiFi();

void disconnectWiFi();

bool reconnectWiFi();

/*******************************************************
 * LOOP
 *******************************************************/
void wifiLoop();

/*******************************************************
 * STATUS
 *******************************************************/
bool isWiFiConnected();

IPAddress getWiFiIP();

int getWiFiRSSI();

String getWiFiMAC();

/*******************************************************
 * CLIENT ACCESS
 *******************************************************/
WiFiClient& getWiFiClient();

#endif