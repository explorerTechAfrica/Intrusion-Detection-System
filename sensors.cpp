#include "sensors.h"

#include "logger.h"

#include "sensor_reader.h"
#include "sensor_detector.h"

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeSensors()
{
    initializeSensorReader();

    initializeSensorDetector();

    LOG_INFO("Sensor Manager Initialized");
}

/*******************************************************
 * MAIN LOOP
 *******************************************************/
void sensorsLoop()
{
    // Read all physical sensors
    updateSensorState();

    // Process detection logic
    sensorDetectorLoop();
}