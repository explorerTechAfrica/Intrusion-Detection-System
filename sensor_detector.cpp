#include "sensor_detector.h"

#include "config.h"
#include "logger.h"
#include "sensor_reader.h"
#include "app.h"

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static bool waitingConfirmation = false;

static unsigned long detectionStart = 0;

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeSensorDetector()
{
    waitingConfirmation = false;

    detectionStart = 0;

    LOG_INFO("Sensor Detector Initialized");
}

/*******************************************************
 * CHECK DETECTION MODE
 *******************************************************/
static bool detectionSatisfied()
{
#if DETECTION_MODE == DETECTION_PIR_ONLY

    return getPIRState();

#elif DETECTION_MODE == DETECTION_IR_ONLY

    return getIRState();

#elif DETECTION_MODE == DETECTION_PIR_OR_IR

    return (getPIRState() || getIRState());

#elif DETECTION_MODE == DETECTION_PIR_AND_IR

    return (getPIRState() && getIRState());

#else

    return false;

#endif
}

/*******************************************************
 * LOOP
 *******************************************************/
void sensorDetectorLoop()
{
    if (!isSystemArmed())
        return;

    bool detected = detectionSatisfied();

    if (!waitingConfirmation)
    {
        if (detected)
        {
            waitingConfirmation = true;
            detectionStart = millis();
        }

        return;
    }

    // Detection disappeared before confirmation
    if (!detected)
    {
        waitingConfirmation = false;
        return;
    }

    // Detection has remained active long enough
    if ((millis() - detectionStart) >= PIR_CONFIRMATION_TIME)
    {
        waitingConfirmation = false;

#if DETECTION_MODE == DETECTION_PIR_ONLY
        reportIntrusion("PIR");

#elif DETECTION_MODE == DETECTION_IR_ONLY
        reportIntrusion("IR");

#elif DETECTION_MODE == DETECTION_PIR_OR_IR
        reportIntrusion("PIR_OR_IR");

#elif DETECTION_MODE == DETECTION_PIR_AND_IR
        reportIntrusion("PIR_AND_IR");

#else
        reportIntrusion("UNKNOWN");
#endif
    }
}