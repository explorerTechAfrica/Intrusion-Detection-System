#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

/**********************************************************************
 * PROJECT INFORMATION
 *********************************************************************/
#define PROJECT_NAME            "Smart Intrusion Detection System"
#define PROJECT_VERSION         "1.0.0"

#define NODE_ID                 "ENTRANCE_01"

/**********************************************************************
 * HARDWARE CONFIGURATION
 *********************************************************************/
#define STATUS_LED_PIN          2

#define PIR_PIN                 13
#define IR_PIN                  12

#define BUZZER_PIN              26

/**********************************************************************
 * SIM800L UART
 *********************************************************************/
#define SIM800_RX_PIN           16      // ESP32 RX2
#define SIM800_TX_PIN           17      // ESP32 TX2

#define SIM800_BAUDRATE         9600

/**********************************************************************
 * MQTT CONFIGURATION
 *********************************************************************/
#define MQTT_PORT               1883
#define MQTT_KEEPALIVE          60
#define MQTT_BUFFER_SIZE        512

/**********************************************************************
 * NETWORK PRIORITY
 *********************************************************************/
enum NetworkPriority
{
    WIFI_FIRST = 0,
    GSM_FIRST
};

#define NETWORK_PRIORITY WIFI_FIRST

/**********************************************************************
 * DETECTION MODES
 *********************************************************************/
enum DetectionMode
{
    DETECT_PIR_ONLY = 0,
    DETECT_IR_ONLY,
    DETECT_PIR_OR_IR,
    DETECT_PIR_AND_IR
};

#define DETECTION_MODE DETECT_PIR_AND_IR

/**********************************************************************
 * SYSTEM TIMERS (milliseconds)
 *********************************************************************/
#define PIR_CONFIRMATION_TIME   2000UL

#define ALARM_DURATION          10000UL

#define COOLDOWN_DURATION       30000UL

#define HEARTBEAT_INTERVAL      60000UL

#define NETWORK_RETRY_INTERVAL  10000UL

#define WIFI_CONNECT_TIMEOUT    15000UL

#define GPRS_CONNECT_TIMEOUT    60000UL

/**********************************************************************
 * SENSOR SAMPLING
 *********************************************************************/
#define SENSOR_SAMPLE_INTERVAL  50UL

/**********************************************************************
 * JSON DOCUMENT SIZE
 *********************************************************************/
#define JSON_DOC_SIZE           512

/**********************************************************************
 * TOPIC ROOT
 *********************************************************************/
#define MQTT_TOPIC_ROOT         "security"

/**********************************************************************
 * LOGGING
 *********************************************************************/
#define ENABLE_SERIAL_LOG       true
#define ENABLE_MQTT_LOG         true
#define ENABLE_DEBUG_LOG        true

/**********************************************************************
 * EVENT BUFFER
 *********************************************************************/
#define MAX_EVENT_ID_LENGTH     40
#define MAX_TOPIC_LENGTH        80
#define MAX_MESSAGE_LENGTH      256

/**********************************************************************
 * FEATURE FLAGS
 *********************************************************************/
#define USE_WIFI               true
#define USE_GSM                true
#define USE_MQTT               true
#define USE_WEB_CONFIG         true
#define USE_STORAGE            true

#define USE_BUZZER             true
#define USE_STATUS_LED         true

/**********************************************************************
 * SENSOR POLARITY
 *********************************************************************/
#define PIR_ACTIVE_LEVEL       HIGH
#define IR_ACTIVE_LEVEL        LOW

/**********************************************************************
 * RETRY COUNTS
 *********************************************************************/
#define WIFI_MAX_RETRIES       3
#define GSM_MAX_RETRIES        3
#define MQTT_MAX_RETRIES       5

/**********************************************************************
 * LED
 *********************************************************************/
#define LED_BLINK_INTERVAL     250UL

/**********************************************************************
 * EVENT STORAGE
 *********************************************************************/
#define EVENT_QUEUE_SIZE       20

/**********************************************************************
 * FIRMWARE
 *********************************************************************/
#define FIRMWARE_NAME          "IDS-ESP32"
#define FIRMWARE_BUILD         "2026.07.30"

#endif