#include "mqtt_topics.h"

#include "config.h"
#include "secrets.h"

/*******************************************************
 * PRIVATE TOPICS
 *******************************************************/
static char heartbeatTopic[MAX_TOPIC_LENGTH];
static char statusTopic[MAX_TOPIC_LENGTH];
static char intrusionTopic[MAX_TOPIC_LENGTH];
static char alarmTopic[MAX_TOPIC_LENGTH];
static char networkTopic[MAX_TOPIC_LENGTH];
static char logTopic[MAX_TOPIC_LENGTH];
static char commandTopic[MAX_TOPIC_LENGTH];

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeMQTTTopics()
{
    snprintf(
        heartbeatTopic,
        sizeof(heartbeatTopic),
        "%s/%s/heartbeat",
        MQTT_ROOT_TOPIC,
        NODE_ID);

    snprintf(
        statusTopic,
        sizeof(statusTopic),
        "%s/%s/status",
        MQTT_ROOT_TOPIC,
        NODE_ID);

    snprintf(
        intrusionTopic,
        sizeof(intrusionTopic),
        "%s/%s/intrusion",
        MQTT_ROOT_TOPIC,
        NODE_ID);

    snprintf(
        alarmTopic,
        sizeof(alarmTopic),
        "%s/%s/alarm",
        MQTT_ROOT_TOPIC,
        NODE_ID);

    snprintf(
        networkTopic,
        sizeof(networkTopic),
        "%s/%s/network",
        MQTT_ROOT_TOPIC,
        NODE_ID);

    snprintf(
        logTopic,
        sizeof(logTopic),
        "%s/%s/log",
        MQTT_ROOT_TOPIC,
        NODE_ID);

    snprintf(
        commandTopic,
        sizeof(commandTopic),
        "%s/%s/command",
        MQTT_ROOT_TOPIC,
        NODE_ID);
}

/*******************************************************
 * GETTERS
 *******************************************************/
const char* getHeartbeatTopic()
{
    return heartbeatTopic;
}

const char* getStatusTopic()
{
    return statusTopic;
}

const char* getIntrusionTopic()
{
    return intrusionTopic;
}

const char* getAlarmTopic()
{
    return alarmTopic;
}

const char* getNetworkTopic()
{
    return networkTopic;
}

const char* getLogTopic()
{
    return logTopic;
}

const char* getCommandTopic()
{
    return commandTopic;
}