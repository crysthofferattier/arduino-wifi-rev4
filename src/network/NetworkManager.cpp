#include <network/NetworkManager.h>
#include <secrets.h>

NetworkManager::NetworkManager(const char *ssid, const char *password)
{
    _ssid = ssid;
    _password = password;
}

NetworkManager networkManager(SECRET_SSID, SECRET_PASS);

void NetworkManager::connect()
{
    int status = WL_IDLE_STATUS;

    if (WiFi.status() == WL_NO_MODULE)
    {        
        while (true)
            ;
    }

    while (status != WL_CONNECTED)
    {
        status = WiFi.begin(SECRET_SSID, SECRET_PASS);

        delay(5000);
    }
}

void NetworkManager::showNetworkInfo()
{
    // debugManager.debugMessage(debugManager.LOG_INFO, "Attempting to connect to WPA SSID: " + String(SECRET_SSID));
    // debugManager.debugMessage(debugManager.LOG_INFO, "Attempting to connect to WPA SSID: " + WiFi.localIP());
}

bool NetworkManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}