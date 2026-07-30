#ifndef MQTT_COMMANDS_H
#define MQTT_COMMANDS_H

#include <Arduino.h>

/*******************************************************
 * PROCESS MQTT COMMAND
 *******************************************************/
void processMQTTCommand(
    const char* topic,
    const byte* payload,
    unsigned int length);

#endif