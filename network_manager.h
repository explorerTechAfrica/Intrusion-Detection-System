#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <Arduino.h>
#include <Client.h>

/*******************************************************
 * NETWORK TYPE
 *******************************************************/
enum NetworkType
{
    NETWORK_NONE = 0,
    NETWORK_WIFI,
    NETWORK_GPRS
};

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeNetwork();

/*******************************************************
 * CONNECTION
 *******************************************************/
bool connectNetwork();

bool switchToWiFi();

bool switchToGPRS();

/*******************************************************
 * LOOP
 *******************************************************/
void networkLoop();

/*******************************************************
 * STATUS
 *******************************************************/
bool isNetworkConnected();

NetworkType getActiveNetwork();

const char* getActiveNetworkName();

/*******************************************************
 * CLIENT
 *******************************************************/
Client& getActiveClient();

#endif