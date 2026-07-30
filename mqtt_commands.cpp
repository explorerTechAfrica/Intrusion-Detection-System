#include "mqtt_commands.h"

#include "logger.h"
#include "mqtt_manager.h"

#include <ArduinoJson.h>

/*******************************************************
 * APPLICATION FUNCTIONS
 * (Implemented later in app.cpp)
 *******************************************************/
extern void armSystem();
extern void disarmSystem();
extern void sirenOn();
extern void sirenOff();
extern void rebootSystem();

/*******************************************************
 * PROCESS COMMAND
 *******************************************************/
void processMQTTCommand(
        const char* topic,
        const byte* payload,
        unsigned int length)
{
    JsonDocument doc;

    DeserializationError err =
        deserializeJson(doc, payload, length);

    if (err)
    {
        LOG_ERROR("Invalid MQTT JSON");

        return;
    }

    if (!doc["command"].is<const char*>())
    {
        LOG_ERROR("Missing command");

        return;
    }

    const char* command =
        doc["command"];

    LOG_INFOF(
        "MQTT Command: %s",
        command);

    /***************************************************
     * ARM
     ***************************************************/
    if (strcmp(command, "ARM") == 0)
    {
        armSystem();

        publishStatus("ARMED");

        return;
    }

    /***************************************************
     * DISARM
     ***************************************************/
    if (strcmp(command, "DISARM") == 0)
    {
        disarmSystem();

        publishStatus("DISARMED");

        return;
    }

    /***************************************************
     * STATUS
     ***************************************************/
    if (strcmp(command, "STATUS") == 0)
    {
        publishHeartbeat();

        return;
    }

    /***************************************************
     * SIREN ON
     ***************************************************/
    if (strcmp(command, "SIREN_ON") == 0)
    {
        sirenOn();

        publishAlarm(true);

        return;
    }

    /***************************************************
     * SIREN OFF
     ***************************************************/
    if (strcmp(command, "SIREN_OFF") == 0)
    {
        sirenOff();

        publishAlarm(false);

        return;
    }

    /***************************************************
     * REBOOT
     ***************************************************/
    if (strcmp(command, "REBOOT") == 0)
    {
        publishStatus("REBOOTING");

        delay(1000);

        rebootSystem();

        return;
    }

    LOG_WARNF(
        "Unknown Command: %s",
        command);
}