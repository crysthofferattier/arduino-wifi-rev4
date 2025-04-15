#include <network/NetworkManager.h>
#include <secrets.h>

NetworkManager::NetworkManager(const char *ssid, const char *password)
{
    _ssid = ssid;
    _password = password;
}

void NetworkManager::connect()
{
    int status = WL_IDLE_STATUS;

    if (WiFi.status() == WL_NO_MODULE)
    {
        Serial.println("Communication with WiFi module failed!");
        while (true)
            ;
    }

    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(SECRET_SSID);

        status = WiFi.begin(SECRET_SSID, SECRET_PASS);

        delay(5000);
    }
}

void NetworkManager::showNetworkInfo()
{
    Serial.print("SSID: ");
    Serial.println(SECRET_SSID);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

bool NetworkManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}