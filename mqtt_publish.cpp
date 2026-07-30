#include "mqtt_manager.h"
#include "mqtt_topics.h"

#include "config.h"
#include "network_manager.h"
#include "wifi_manager.h"
#include "gsm_manager.h"
#include "logger.h"

#include <ArduinoJson.h>

/*******************************************************
 * PUBLISH HEARTBEAT
 *******************************************************/
bool publishHeartbeat()
{
    if (!isMQTTConnected())
        return false;

    JsonDocument doc;

    doc["node"] = NODE_ID;
    doc["project"] = PROJECT_NAME;
    doc["version"] = PROJECT_VERSION;
    doc["uptime"] = millis();
    doc["network"] = getActiveNetworkName();

    if (getActiveNetwork() == NETWORK_WIFI)
        doc["signal"] = getWiFiRSSI();
    else
        doc["signal"] = getSignalStrength();

    char payload[256];

    serializeJson(doc, payload);

    return getMQTTClient().publish(
            getHeartbeatTopic(),
            payload);
}

/*******************************************************
 * PUBLISH STATUS
 *******************************************************/
bool publishStatus(const char* status)
{
    if (!isMQTTConnected())
        return false;

    JsonDocument doc;

    doc["node"] = NODE_ID;
    doc["status"] = status;
    doc["time"] = millis();

    char payload[200];

    serializeJson(doc, payload);

    return getMQTTClient().publish(
            getStatusTopic(),
            payload,
            true);
}

/*******************************************************
 * PUBLISH NETWORK
 *******************************************************/
bool publishNetwork()
{
    if (!isMQTTConnected())
        return false;

    JsonDocument doc;

    doc["node"] = NODE_ID;
    doc["network"] = getActiveNetworkName();

    if(getActiveNetwork()==NETWORK_WIFI)
        doc["signal"]=getWiFiRSSI();
    else
        doc["signal"]=getSignalStrength();

    char payload[200];

    serializeJson(doc,payload);

    return getMQTTClient().publish(
            getNetworkTopic(),
            payload);
}

/*******************************************************
 * PUBLISH ALARM
 *******************************************************/
bool publishAlarm(bool active)
{
    if (!isMQTTConnected())
        return false;

    JsonDocument doc;

    doc["node"]=NODE_ID;
    doc["alarm"]=active;
    doc["time"]=millis();

    char payload[200];

    serializeJson(doc,payload);

    return getMQTTClient().publish(
            getAlarmTopic(),
            payload);
}

/*******************************************************
 * PUBLISH LOG
 *******************************************************/
bool publishLog(
        const char* level,
        const char* message)
{
    if (!isMQTTConnected())
        return false;

    JsonDocument doc;

    doc["node"]=NODE_ID;
    doc["level"]=level;
    doc["message"]=message;
    doc["time"]=millis();

    char payload[256];

    serializeJson(doc,payload);

    return getMQTTClient().publish(
            getLogTopic(),
            payload);
}