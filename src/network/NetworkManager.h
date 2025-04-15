#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <WiFiS3.h>
#include <Arduino.h>

class NetworkManager
{
public:
    NetworkManager(const char *ssid, const char *password);

    void connect();
    bool isConnected();
    void showNetworkInfo();

private:
    const char *_ssid;
    const char *_password;
};

#endif