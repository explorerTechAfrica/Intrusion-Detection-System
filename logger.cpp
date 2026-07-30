#include "logger.h"
#include "config.h"

#include <stdarg.h>

/*******************************************************
 * LOCAL FUNCTION
 *******************************************************/
static void printLog(const char* level, const char* message)
{
#if ENABLE_SERIAL_LOG

    Serial.print("[");

    Serial.print(millis());

    Serial.print("] ");

    Serial.print(level);

    Serial.print(" : ");

    Serial.println(message);

#endif
}

/*******************************************************
 * PRINTF LOGGER
 *******************************************************/
static void printLogf(const char* level,
                      const char* format,
                      va_list args)
{
#if ENABLE_SERIAL_LOG

    char buffer[256];

    vsnprintf(buffer, sizeof(buffer), format, args);

    printLog(level, buffer);

#endif
}

/*******************************************************
 * INITIALIZE
 *******************************************************/
void initializeLogger()
{
#if ENABLE_SERIAL_LOG

    Serial.begin(115200);

    delay(100);

    Serial.println();

    Serial.println("======================================");

    Serial.println(PROJECT_NAME);

    Serial.print("Version : ");

    Serial.println(PROJECT_VERSION);

    Serial.println("Logger Initialized");

    Serial.println("======================================");

#endif
}

/*******************************************************
 * SIMPLE LOGS
 *******************************************************/
void logInfo(const char* message)
{
    printLog("INFO", message);
}

void logWarning(const char* message)
{
    printLog("WARN", message);
}

void logError(const char* message)
{
    printLog("ERROR", message);
}

void logDebug(const char* message)
{
#if ENABLE_DEBUG_LOG
    printLog("DEBUG", message);
#endif
}

/*******************************************************
 * FORMATTED LOGS
 *******************************************************/
void logInfof(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    printLogf("INFO", format, args);

    va_end(args);
}

void logWarningf(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    printLogf("WARN", format, args);

    va_end(args);
}

void logErrorf(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    printLogf("ERROR", format, args);

    va_end(args);
}

void logDebugf(const char *format, ...)
{
#if ENABLE_DEBUG_LOG

    va_list args;

    va_start(args, format);

    printLogf("DEBUG", format, args);

    va_end(args);

#endif
}