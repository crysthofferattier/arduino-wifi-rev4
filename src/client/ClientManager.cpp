#include <client/ClientManager.h>
#include <debug/DebugManager.h>
#include <constants.h>

DebugManager debugManager;

ClientManager::ClientManager()
{
    _client = WiFiSSLClient();
};

String ClientManager::get(String endpoint, const char *host, int port)
{
    if (_client.connect(host, port))
    {
        Serial.println("Connected to server.");

        _client.println("GET " + endpoint + " HTTP/1.1");
        _client.print("Host: ");
        _client.println(host);
        _client.println("Connection: close");
        _client.println("Accept: application/json\r\n\r\n");
        _client.println();    

        return readResponse();
    }
    else
    {
        Serial.print("Connection to: ");
        Serial.print(host);
        Serial.println(" Failed!");
    }

    return "";
}

String ClientManager::readResponse()
{
    String response = "";

    // Wait for the response
    while (!_client.available())
    {
        Serial.println("Waiting for client");
        delay(100);
    }

    while (_client.available())
    {
        response += char(_client.read());
    }

    _client.stop();

    return response;
}