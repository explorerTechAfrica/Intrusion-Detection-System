#include "gsm_manager.h"

#include "config.h"
#include "secrets.h"
#include "logger.h"

#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>

/*******************************************************
 * PRIVATE OBJECTS
 *******************************************************/
static HardwareSerial SerialAT(2);

static TinyGsm modem(SerialAT);

static TinyGsmClient gsmClient(modem);

/*******************************************************
 * PRIVATE VARIABLES
 *******************************************************/
static bool gsmInitialized = false;

static unsigned long reconnectTimer = 0;

/*******************************************************
 * INITIALIZATION
 *******************************************************/
void initializeGSM()
{
    if (gsmInitialized)
        return;

    SerialAT.begin(
        SIM800_BAUDRATE,
        SERIAL_8N1,
        SIM800_RX_PIN,
        SIM800_TX_PIN);

    delay(3000);

    LOG_INFO("Initializing SIM800L...");

    modem.restart();

    if (strlen(GSM_PIN) > 0)
    {
        modem.simUnlock(GSM_PIN);
    }

    gsmInitialized = true;

    LOG_INFO("SIM800L Ready");
}

/*******************************************************
 * CONNECT
 *******************************************************/
bool connectGPRS()
{
    if (!gsmInitialized)
        initializeGSM();

    LOG_INFO("Waiting for GSM Network...");

    if (!modem.waitForNetwork(GPRS_CONNECT_TIMEOUT))
    {
        LOG_ERROR("No GSM Network");

        return false;
    }

    LOG_INFO("Network Registered");

    LOG_INFOF("Operator : %s",
              modem.getOperator().c_str());

    LOG_INFO("Connecting GPRS...");

    if (!modem.gprsConnect(
            GSM_APN,
            GSM_USER,
            GSM_PASSWORD))
    {
        LOG_ERROR("GPRS Connection Failed");

        return false;
    }

    LOG_INFO("GPRS Connected");

    LOG_INFOF("Signal Strength : %d",
              modem.getSignalQuality());

    return true;
}

/*******************************************************
 * DISCONNECT
 *******************************************************/
void disconnectGPRS()
{
    modem.gprsDisconnect();

    LOG_INFO("GPRS Disconnected");
}

/*******************************************************
 * RECONNECT
 *******************************************************/
bool reconnectGPRS()
{
    disconnectGPRS();

    delay(1000);

    return connectGPRS();
}

/*******************************************************
 * LOOP
 *******************************************************/
void gsmLoop()
{
    if (modem.isGprsConnected())
        return;

    if ((millis() - reconnectTimer) < NETWORK_RETRY_INTERVAL)
        return;

    reconnectTimer = millis();

    LOG_WARN("Attempting GSM Reconnect...");

    reconnectGPRS();
}

/*******************************************************
 * STATUS
 *******************************************************/
bool isGSMConnected()
{
    return modem.isNetworkConnected();
}

bool isGPRSConnected()
{
    return modem.isGprsConnected();
}

int getSignalStrength()
{
    return modem.getSignalQuality();
}

String getOperatorName()
{
    return modem.getOperator();
}

/*******************************************************
 * CLIENT ACCESS
 *******************************************************/
TinyGsmClient& getGSMClient()
{
    return gsmClient;
}