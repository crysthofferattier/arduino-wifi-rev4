#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <constants.h>
#include <Arduino.h>
#include <WiFiS3.h>

class ClientManager
{
public:
    ClientManager();

    String get(String endpoint, const char *host = SERVER_ADDR, int port = SERVER_PORT);
    String post(String URL, String endpoint);
    String readResponse();

private:
    WiFiSSLClient _client;
    String _host;
    int _port;
};

extern ClientManager clientManager;  // Declaration as extern

#endif