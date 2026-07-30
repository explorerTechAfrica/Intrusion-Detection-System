#ifndef GSM_MANAGER_H
#define GSM_MANAGER_H

#include <Arduino.h>
#include <TinyGsmClient.h>

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeGSM();

/*******************************************************
 * CONNECTION
 *******************************************************/
bool connectGPRS();

void disconnectGPRS();

bool reconnectGPRS();

/*******************************************************
 * LOOP
 *******************************************************/
void gsmLoop();

/*******************************************************
 * STATUS
 *******************************************************/
bool isGSMConnected();

bool isGPRSConnected();

int getSignalStrength();

String getOperatorName();

/*******************************************************
 * CLIENT ACCESS
 *******************************************************/
TinyGsmClient& getGSMClient();

#endif