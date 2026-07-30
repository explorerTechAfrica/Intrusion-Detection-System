#ifndef SENSOR_READER_H
#define SENSOR_READER_H

#include <Arduino.h>

/*******************************************************
 * SENSOR DATA
 *******************************************************/
struct SensorState
{
    bool pir;
    bool ir;
};

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeSensorReader();

/*******************************************************
 * UPDATE
 *******************************************************/
void updateSensorState();

/*******************************************************
 * ACCESS
 *******************************************************/
bool getPIRState();

bool getIRState();

SensorState getSensorState();

#endif