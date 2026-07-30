#include "wifi_manager.h"

#include "config.h"
#include "secrets.h"
#include "logger.h"

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static WiFiClient wifiClient;

static bool wifiInitialized = false;

static unsigned long reconnectTimer = 0;

/*******************************************************
 * INITIALIZE
 *******************************************************/
void initializeWiFi()
{
    if (wifiInitialized)
        return;

    WiFi.mode(WIFI_STA);

    WiFi.setAutoReconnect(true);

    WiFi.persistent(false);

    wifiInitialized = true;

    LOG_INFO("WiFi Manager Initialized");
}

/*******************************************************
 * CONNECT
 *******************************************************/
bool connectWiFi()
{
    if (!wifiInitialized)
        initializeWiFi();

    if (WiFi.status() == WL_CONNECTED)
        return true;

    LOG_INFOF("Connecting to WiFi: %s", WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);

        if ((millis() - start) >= WIFI_CONNECT_TIMEOUT)
        {
            LOG_WARN("WiFi Connection Timeout");

            return false;
        }
    }

    LOG_INFO("WiFi Connected");

    LOG_INFOF("IP Address : %s",
              WiFi.localIP().toString().c_str());

    LOG_INFOF("RSSI : %d dBm",
              WiFi.RSSI());

    return true;
}

/*******************************************************
 * DISCONNECT
 *******************************************************/
void disconnectWiFi()
{
    WiFi.disconnect(true);

    LOG_INFO("WiFi Disconnected");
}

/*******************************************************
 * RECONNECT
 *******************************************************/
bool reconnectWiFi()
{
    disconnectWiFi();

    delay(1000);

    return connectWiFi();
}

/*******************************************************
 * LOOP
 *******************************************************/
void wifiLoop()
{
    if (WiFi.status() == WL_CONNECTED)
        return;

    if ((millis() - reconnectTimer) < NETWORK_RETRY_INTERVAL)
        return;

    reconnectTimer = millis();

    LOG_WARN("Attempting WiFi Reconnect...");

    reconnectWiFi();
}

/*******************************************************
 * STATUS
 *******************************************************/
bool isWiFiConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}

IPAddress getWiFiIP()
{
    return WiFi.localIP();
}

int getWiFiRSSI()
{
    return WiFi.RSSI();
}

String getWiFiMAC()
{
    return WiFi.macAddress();
}

/*******************************************************
 * CLIENT
 *******************************************************/
WiFiClient& getWiFiClient()
{
    return wifiClient;
}