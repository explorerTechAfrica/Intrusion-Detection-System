#ifndef APP_H
#define APP_H

#include <Arduino.h>

/*******************************************************
 * SYSTEM STATES
 *******************************************************/
enum SystemState
{
    SYSTEM_DISARMED = 0,
    SYSTEM_ARMED,
    SYSTEM_ALARM,
    SYSTEM_COOLDOWN
};

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeApplication();

/*******************************************************
 * MAIN LOOP
 *******************************************************/
void applicationLoop();

/*******************************************************
 * ARMING
 *******************************************************/
void armSystem();

void disarmSystem();

bool isSystemArmed();

/*******************************************************
 * ALARM
 *******************************************************/
void sirenOn();

void sirenOff();

bool isAlarmActive();

/*******************************************************
 * INTRUSION
 *******************************************************/
void reportIntrusion(const char* sensor);

bool isIntrusionDetected();

/*******************************************************
 * SYSTEM
 *******************************************************/
SystemState getSystemState();

void rebootSystem();

#endif