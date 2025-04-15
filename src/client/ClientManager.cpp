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

    return "";
}

String ClientManager::readResponse()
{
    String response = "";
    bool isBody = false;

    unsigned long timeout = millis(); // prevent getting stuck
    while (_client.connected() && millis() - timeout < 5000)
    {
        while (_client.available())
        {
            String line = _client.readStringUntil('\n');
            line.trim(); // remove \r or extra whitespace

            if (!isBody)
            {
                if (line.length() == 0)
                {
                    isBody = true; // blank line = end of headers
                }
            }
            else
            {
                response += line;
            }
        }
    }

    _client.stop();
    Serial.println("Response body:");
    //response.trim();
    Serial.println(response);

    return response;
}