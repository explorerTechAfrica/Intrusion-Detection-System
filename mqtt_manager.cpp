#include "mqtt_manager.h"
#include "mqtt_commands.h"

#include "config.h"
#include "secrets.h"
#include "logger.h"
#include "network_manager.h"
#include "mqtt_topics.h"

#include <PubSubClient.h>
#include <ArduinoJson.h>

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/

// MQTT Client
static PubSubClient mqtt;

// MQTT Client ID
static char clientID[40];

// Connection timer
static unsigned long reconnectTimer = 0;


/*******************************************************
 * INITIALIZE MQTT
 *******************************************************/
void initializeMQTT()
{
    mqtt.setClient(getActiveClient());

    mqtt.setServer(MQTT_BROKER, MQTT_PORT);

    mqtt.setBufferSize(MQTT_BUFFER_SIZE);

    mqtt.setKeepAlive(MQTT_KEEPALIVE);

    mqtt.setCallback(mqttCallback);

    initializeMQTTTopics();

    snprintf(clientID,
             sizeof(clientID),
             "%s%s",
             MQTT_CLIENT_PREFIX,
             NODE_ID);

    LOG_INFO("MQTT Manager Initialized");
}

/*******************************************************
 * CONNECT MQTT
 *******************************************************/
bool connectMQTT()
{
    if (!isNetworkConnected())
        return false;

    mqtt.setClient(getActiveClient());

    LOG_INFO("Connecting MQTT...");

    if (!mqtt.connect(
            clientID,
            MQTT_USERNAME,
            MQTT_PASSWORD))
    {
        LOG_ERROR("MQTT Connection Failed");

        return false;
    }

    LOG_INFO("MQTT Connected");

    mqtt.subscribe(getCommandTopic());

    publishStatus("ONLINE");

    return true;
}

/*******************************************************
 * RECONNECT
 *******************************************************/
bool reconnectMQTT()
{
    if (mqtt.connected())
        return true;

    if ((millis() - reconnectTimer) < NETWORK_RETRY_INTERVAL)
        return false;

    reconnectTimer = millis();

    return connectMQTT();
}

/*******************************************************
 * DISCONNECT
 *******************************************************/
void disconnectMQTT()
{
    mqtt.disconnect();

    LOG_INFO("MQTT Disconnected");
}

/*******************************************************
 * LOOP
 *******************************************************/
void mqttLoop()
{
    if (!mqtt.connected())
    {
        reconnectMQTT();

        return;
    }

    mqtt.loop();
}


/*******************************************************
 * STATUS
 *******************************************************/
bool isMQTTConnected()
{
    return mqtt.connected();
}

/*******************************************************
 * MQTT CALLBACK
 *******************************************************/
void mqttCallback(
        char* topic,
        byte* payload,
        unsigned int length)
{
    LOG_INFOF(
        "MQTT RX: %s",
        topic);

    processMQTTCommand(
        topic,
        payload,
        length);
}

/*******************************************************
 * CLIENT ACCESS
 *******************************************************/
PubSubClient& getMQTTClient()
{
    return mqtt;
}

