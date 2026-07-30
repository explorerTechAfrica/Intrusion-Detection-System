#include "event_manager.h"

#include "config.h"
#include "mqtt_manager.h"
#include "mqtt_topics.h"
#include "network_manager.h"
#include "wifi_manager.h"
#include "gsm_manager.h"

#include <ArduinoJson.h>

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static uint32_t sequenceNumber = 0;

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeEventManager()
{
    sequenceNumber = 0;
}

/*******************************************************
 * NEXT SEQUENCE
 *******************************************************/
uint32_t getNextSequence()
{
    sequenceNumber++;

    return sequenceNumber;
}

/*******************************************************
 * EVENT ID
 *******************************************************/
void generateEventID(char* buffer, size_t len)
{
    snprintf(
        buffer,
        len,
        "%s-%010lu",
        NODE_ID,
        (unsigned long)getNextSequence());
}

/*******************************************************
 * PUBLISH INTRUSION
 *******************************************************/
bool publishIntrusion(
        const char* sensor,
        bool alarm)
{
    if(!isMQTTConnected())
        return false;

    JsonDocument doc;

    char eventID[40];

    generateEventID(
        eventID,
        sizeof(eventID));

    doc["event_id"]=eventID;

    doc["sequence"]=sequenceNumber;

    doc["node"]=NODE_ID;

    doc["sensor"]=sensor;

    doc["alarm"]=alarm;

    doc["time"]=millis();

    doc["network"]=getActiveNetworkName();

    if(getActiveNetwork()==NETWORK_WIFI)
        doc["signal"]=getWiFiRSSI();
    else
        doc["signal"]=getSignalStrength();

    char payload[350];

    serializeJson(doc,payload);

    return getMQTTClient().publish(
            getIntrusionTopic(),
            payload);
}