#include "sensor_reader.h"

#include "config.h"
#include "logger.h"

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static SensorState sensors;

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeSensorReader()
{
    pinMode(PIR_PIN, INPUT);

    pinMode(IR_PIN, INPUT);

    sensors.pir = false;

    sensors.ir = false;

    LOG_INFO("Sensor Reader Initialized");
}

/*******************************************************
 * UPDATE SENSOR STATES
 *******************************************************/
void updateSensorState()
{
    sensors.pir = digitalRead(PIR_PIN);

    sensors.ir = digitalRead(IR_PIN);
}

/*******************************************************
 * GET PIR
 *******************************************************/
bool getPIRState()
{
    return sensors.pir;
}

/*******************************************************
 * GET IR
 *******************************************************/
bool getIRState()
{
    return sensors.ir;
}

/*******************************************************
 * GET BOTH
 *******************************************************/
SensorState getSensorState()
{
    return sensors;
}