#include <client/ClientManager.h>
#include <constants.h>

ClientManager::ClientManager()
{
    _client = WiFiSSLClient();
};

ClientManager clientManager;

String ClientManager::get(String endpoint, const char *host, int port)
{
    if (_client.connect(host, port))
    {
        _client.println("GET " + endpoint + " HTTP/1.1");
        _client.print("Host: ");
        _client.println(host);
        _client.println("Connection: close");
        _client.println("Accept: application/json\r\n\r\n");
        _client.println();    

        return readResponse();
    }

    return "";
}

String ClientManager::readResponse()
{
    String response = "";

    // Wait for the response
    while (!_client.available())
    {
        delay(100);
    }

    while (_client.available())
    {
        response += char(_client.read());
    }

    _client.stop();

    return response;
}