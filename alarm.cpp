#include "alarm.h"

#include "config.h"
#include "logger.h"

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static bool alarmRunning = false;

static unsigned long alarmStartTime = 0;

static unsigned long ledTimer = 0;

static bool ledState = false;

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeAlarm()
{
#if USE_BUZZER
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
#endif

#if USE_STATUS_LED
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);
#endif

    alarmRunning = false;

    LOG_INFO("Alarm Initialized");
}

/*******************************************************
 * START ALARM
 *******************************************************/
void startAlarm()
{
    if (alarmRunning)
        return;

    alarmRunning = true;

    alarmStartTime = millis();

#if USE_BUZZER
    digitalWrite(BUZZER_PIN, HIGH);
#endif

    LOG_WARN("Alarm Started");
}

/*******************************************************
 * STOP ALARM
 *******************************************************/
void stopAlarm()
{
    alarmRunning = false;

#if USE_BUZZER
    digitalWrite(BUZZER_PIN, LOW);
#endif

#if USE_STATUS_LED
    digitalWrite(STATUS_LED_PIN, LOW);
#endif

    LOG_INFO("Alarm Stopped");
}

/*******************************************************
 * LOOP
 *******************************************************/
void alarmLoop()
{
    if (!alarmRunning)
        return;

#if USE_STATUS_LED
    if (millis() - ledTimer >= 250)
    {
        ledTimer = millis();

        ledState = !ledState;

        digitalWrite(STATUS_LED_PIN, ledState);
    }
#endif

    if (millis() - alarmStartTime >= ALARM_DURATION)
    {
        stopAlarm();
    }
}

/*******************************************************
 * STATUS
 *******************************************************/
bool isAlarmRunning()
{
    return alarmRunning;
}