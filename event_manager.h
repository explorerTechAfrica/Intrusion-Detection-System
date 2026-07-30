#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <Arduino.h>

/*******************************************************
 * EVENT TYPES
 *******************************************************/
enum EventType
{
    EVENT_INTRUSION = 0,
    EVENT_ALARM,
    EVENT_SYSTEM,
    EVENT_NETWORK
};

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeEventManager();

/*******************************************************
 * EVENT ID
 *******************************************************/
void generateEventID(char* buffer, size_t len);

/*******************************************************
 * SEQUENCE
 *******************************************************/
uint32_t getNextSequence();

/*******************************************************
 * PUBLISH
 *******************************************************/
bool publishIntrusion(
        const char* sensor,
        bool alarm);

#endif