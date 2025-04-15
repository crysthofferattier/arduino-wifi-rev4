#include <client/ClientManager.h>
#include <debug/DebugManager.h>
#include <constants.h>

DebugManager debugManager;

ClientManager::ClientManager()
{
    _client = WiFiClient();
};

String ClientManager::get(String endpoint, const char *host, int port)
{
    Serial.println(host);
    Serial.println(endpoint);
    Serial.println(port);
    
    if (_client.connect(host, port))
    {
        _client.println("GET /" + endpoint + " HTTP/1.1");
        _client.println("Host: arduinowifimarco.ie");
        _client.println("Connection: close");
        _client.println();

        return readResponse();
    }

    return "";
}

String ClientManager::readResponse()
{
    String response = "";
    bool isBody = false;

    while (_client.connected())
    {
        while (_client.available())
        {
            String line = _client.readStringUntil('\n');

            if (line == "\r")
            {
                isBody = true;
                continue;
            }

            if (isBody)
            {
                response += line;
            }
        }
    }

    _client.stop();
    Serial.println("Print response!");
    Serial.println(response);

    return response;
}