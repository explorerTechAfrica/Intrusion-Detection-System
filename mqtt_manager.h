#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <PubSubClient.h>

PubSubClient& getMQTTClient();

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeMQTT();

/*******************************************************
 * CONNECTION
 *******************************************************/
bool connectMQTT();

bool reconnectMQTT();

void disconnectMQTT();

/*******************************************************
 * LOOP
 *******************************************************/
void mqttLoop();

/*******************************************************
 * STATUS
 *******************************************************/
bool isMQTTConnected();

/*******************************************************
 * PUBLISH FUNCTIONS
 *******************************************************/
bool publishHeartbeat();

bool publishStatus(const char* status);

bool publishIntrusion(
    const char* sensor,
    bool alarm);

bool publishAlarm(
    bool active);

bool publishNetwork();

bool publishLog(
    const char* level,
    const char* message);

/*******************************************************
 * COMMANDS
 *******************************************************/
void mqttCallback(
    char* topic,
    byte* payload,
    unsigned int length);

#endif