#include "config.h"
#include "secrets.h"

#include "logger.h"

#include "wifi_manager.h"
#include "gsm_manager.h"
#include "network_manager.h"

#include "mqtt_topics.h"
#include "mqtt_manager.h"

#include "event_manager.h"

#include "alarm.h"

#include "sensor_reader.h"
#include "sensor_detector.h"
#include "sensors.h"

#include "app.h"

/*******************************************************
 * SETUP
 *******************************************************/
void setup()
{
    Serial.begin(115200);

    delay(1000);

    LOG_INFO("========================================");
    LOG_INFO(PROJECT_NAME);
    LOG_INFO(PROJECT_VERSION);
    LOG_INFO("ESP32 Intrusion Detection System");
    LOG_INFO("Booting...");
    LOG_INFO("========================================");

    /***************************************************
     * Initialize Core Modules
     ***************************************************/
    initializeApplication();

    initializeAlarm();

    initializeSensors();

    initializeEventManager();

    /***************************************************
     * Initialize Network
     ***************************************************/
    initializeWiFi();

    initializeGSM();

    initializeNetwork();

    /***************************************************
     * Initialize MQTT
     ***************************************************/
    initializeMQTTTopics();

    initializeMQTT();

    connectNetwork();

    connectMQTT();

    publishStatus("ONLINE");

    LOG_INFO("System Ready");
}

/*******************************************************
 * LOOP
 *******************************************************/
void loop()
{
    /***************************************************
     * Maintain Network
     ***************************************************/
    networkLoop();

    /***************************************************
     * Maintain MQTT
     ***************************************************/
    mqttLoop();

    /***************************************************
     * Process Sensors
     ***************************************************/
    sensorsLoop();

    /***************************************************
     * Alarm Processing
     ***************************************************/
    alarmLoop();

    /***************************************************
     * Application Tasks
     ***************************************************/
    applicationLoop();

    /***************************************************
     * Heartbeat
     ***************************************************/
    static unsigned long heartbeatTimer = 0;

    if (millis() - heartbeatTimer >= HEARTBEAT_INTERVAL)
    {
        heartbeatTimer = millis();

        publishHeartbeat();
    }

    delay(5);
}