#include "app.h"

#include "config.h"
#include "logger.h"

#include "alarm.h"
#include "event_manager.h"
#include "mqtt_manager.h"

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static SystemState systemState = SYSTEM_ARMED;

static bool intrusionDetected = false;

static bool alarmActive = false;

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeApplication()
{
    systemState = SYSTEM_ARMED;

    intrusionDetected = false;

    alarmActive = false;

    LOG_INFO("Application Initialized");
}

/*******************************************************
 * MAIN LOOP
 *******************************************************/
void applicationLoop()
{
    // Reserved for future application logic
}

/*******************************************************
 * ARM SYSTEM
 *******************************************************/
void armSystem()
{
    systemState = SYSTEM_ARMED;

    intrusionDetected = false;

    LOG_INFO("System Armed");
}

/*******************************************************
 * DISARM SYSTEM
 *******************************************************/
void disarmSystem()
{
    systemState = SYSTEM_DISARMED;

    intrusionDetected = false;

    sirenOff();

    LOG_INFO("System Disarmed");
}

/*******************************************************
 * STATUS
 *******************************************************/
bool isSystemArmed()
{
    return (systemState == SYSTEM_ARMED);
}

/*******************************************************
 * ALARM ON
 *******************************************************/
void sirenOn()
{
    if (alarmActive)
        return;

    alarmActive = true;

    systemState = SYSTEM_ALARM;

    startAlarm();      // Implemented in alarm.cpp

    publishAlarm(true);

    LOG_WARN("Alarm Activated");
}

/*******************************************************
 * ALARM OFF
 *******************************************************/
void sirenOff()
{
    if (!alarmActive)
        return;

    stopAlarm();

    alarmActive = false;

    if (systemState != SYSTEM_DISARMED)
        systemState = SYSTEM_ARMED;

    publishAlarm(false);

    LOG_INFO("Alarm Stopped");
}

/*******************************************************
 * STATUS
 *******************************************************/
bool isAlarmActive()
{
    return alarmActive;
}

/*******************************************************
 * REPORT INTRUSION
 *******************************************************/
void reportIntrusion(const char* sensor)
{
    if (!isSystemArmed())
        return;

    intrusionDetected = true;

    publishIntrusion(sensor, true);

    sirenOn();

    LOG_WARNF("Intrusion Detected (%s)", sensor);
}

/*******************************************************
 * STATUS
 *******************************************************/
bool isIntrusionDetected()
{
    return intrusionDetected;
}

/*******************************************************
 * STATE
 *******************************************************/
SystemState getSystemState()
{
    return systemState;
}

/*******************************************************
 * REBOOT
 *******************************************************/
void rebootSystem()
{
    LOG_WARN("Restarting ESP32...");

    delay(1000);

    ESP.restart();
}