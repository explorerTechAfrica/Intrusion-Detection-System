#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeLogger();

/*******************************************************
 * LOG FUNCTIONS
 *******************************************************/
void logInfo(const char* message);

void logWarning(const char* message);

void logError(const char* message);

void logDebug(const char* message);

/*******************************************************
 * PRINTF STYLE LOGGING
 *******************************************************/
void logInfof(const char *format, ...);

void logWarningf(const char *format, ...);

void logErrorf(const char *format, ...);

void logDebugf(const char *format, ...);

/*******************************************************
 * LOG MACROS
 *******************************************************/
#define LOG_INFO(x)       logInfo(x)
#define LOG_WARN(x)       logWarning(x)
#define LOG_ERROR(x)      logError(x)
#define LOG_DEBUG(x)      logDebug(x)

#define LOG_INFOF(...)    logInfof(__VA_ARGS__)
#define LOG_WARNF(...)    logWarningf(__VA_ARGS__)
#define LOG_ERRORF(...)   logErrorf(__VA_ARGS__)
#define LOG_DEBUGF(...)   logDebugf(__VA_ARGS__)

#endif