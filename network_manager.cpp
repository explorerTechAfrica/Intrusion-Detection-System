#include "network_manager.h"

#include "wifi_manager.h"
#include "gsm_manager.h"
#include "logger.h"
#include "config.h"

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static NetworkType activeNetwork = NETWORK_NONE;

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeNetwork()
{
    initializeWiFi();

    initializeGSM();

    activeNetwork = NETWORK_NONE;

    LOG_INFO("Network Manager Initialized");
}

/*******************************************************
 * CONNECT NETWORK
 *******************************************************/
bool connectNetwork()
{
#if USE_WIFI

    LOG_INFO("Trying WiFi...");

    if (connectWiFi())
    {
        activeNetwork = NETWORK_WIFI;

        LOG_INFO("Primary Network: WiFi");

        return true;
    }

#endif

#if USE_GSM

    LOG_INFO("Trying GSM...");

    if (connectGPRS())
    {
        activeNetwork = NETWORK_GPRS;

        LOG_INFO("Backup Network: GSM");

        return true;
    }

#endif

    activeNetwork = NETWORK_NONE;

    LOG_ERROR("No Network Available");

    return false;
}

/*******************************************************
 * SWITCH TO WIFI
 *******************************************************/
bool switchToWiFi()
{
#if USE_WIFI

    if (connectWiFi())
    {
        activeNetwork = NETWORK_WIFI;

        LOG_INFO("Switched to WiFi");

        return true;
    }

#endif

    return false;
}

/*******************************************************
 * SWITCH TO GPRS
 *******************************************************/
bool switchToGPRS()
{
#if USE_GSM

    if (connectGPRS())
    {
        activeNetwork = NETWORK_GPRS;

        LOG_INFO("Switched to GSM");

        return true;
    }

#endif

    return false;
}

/*******************************************************
 * NETWORK LOOP
 *******************************************************/
void networkLoop()
{
    switch (activeNetwork)
    {
        case NETWORK_WIFI:

            wifiLoop();

#if USE_GSM

            if (!isWiFiConnected())
            {
                LOG_WARN("WiFi Lost");

                switchToGPRS();
            }

#endif

            break;

        case NETWORK_GPRS:

            gsmLoop();

#if USE_WIFI

            if (isWiFiConnected())
            {
                LOG_INFO("WiFi Restored");

                switchToWiFi();
            }

#endif

            break;

        default:

            connectNetwork();

            break;
    }
}

/*******************************************************
 * STATUS
 *******************************************************/
bool isNetworkConnected()
{
    return (activeNetwork != NETWORK_NONE);
}

NetworkType getActiveNetwork()
{
    return activeNetwork;
}

const char* getActiveNetworkName()
{
    switch (activeNetwork)
    {
        case NETWORK_WIFI:
            return "WiFi";

        case NETWORK_GPRS:
            return "GPRS";

        default:
            return "NONE";
    }
}

/*******************************************************
 * CLIENT
 *******************************************************/
Client& getActiveClient()
{
    if (activeNetwork == NETWORK_WIFI)
    {
        return getWiFiClient();
    }

    return getGSMClient();
}