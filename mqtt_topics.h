#ifndef MQTT_TOPICS_H
#define MQTT_TOPICS_H

#include <Arduino.h>

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeMQTTTopics();

/*******************************************************
 * TOPIC ACCESS
 *******************************************************/
const char* getHeartbeatTopic();

const char* getStatusTopic();

const char* getIntrusionTopic();

const char* getAlarmTopic();

const char* getNetworkTopic();

const char* getLogTopic();

const char* getCommandTopic();

#endif