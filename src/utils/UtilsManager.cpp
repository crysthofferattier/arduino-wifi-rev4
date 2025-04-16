#include <utils/UtilsManager.h>
#include <client/ClientManager.h>
#include <ArduinoJson.h>

#include <RTC.h>

UtilsManager::UtilsManager() {};

void UtilsManager::setupRTCModule()
{
    // String jsonResponse = clientManager.get("/api/time/current/zone?timeZone=Europe%2FDublin", "timeapi.io", 443);
    String jsonResponse = clientManager.get("/posts/1", "jsonplaceholder.typicode.com", 443);
    // String jsonResponse = clientManager.get("/objects?id=3&id=5&id=10", "api.restful-api.dev", 443);

    Serial.println("jsonResponse");
    Serial.println(jsonResponse);
    DynamicJsonDocument jsonObj = parseJson(jsonResponse);

    int year = jsonObj["year"];
    int month = jsonObj["month"];
    int day = jsonObj["day"];
    int hour = jsonObj["hour"];
    int minute = jsonObj["minute"];
    int second = jsonObj["seconds"];

    // Create Time and Date objects
    RTC.begin();

    RTCTime startTime(day, static_cast<Month>(month - 1), year, hour, minute, second, DayOfWeek::WEDNESDAY, SaveLight::SAVING_TIME_ACTIVE);
    RTC.setTime(startTime);
}

String UtilsManager::extractJsonFromChunkedResponse(const String &rawResponse)
{
    int bodyStart = rawResponse.indexOf("\r\n\r\n");
    if (bodyStart == -1)
    {
        Serial.println("No header-body separator found!");
        return "";
    }

    String chunked = rawResponse.substring(bodyStart + 4); // Skip headers
    String decoded = "";

    int pos = 0;
    while (pos < chunked.length())
    {
        // Find the next line which is the chunk size in hex
        int lineEnd = chunked.indexOf("\r\n", pos);
        if (lineEnd == -1)
            break;

        String chunkSizeStr = chunked.substring(pos, lineEnd);
        int chunkSize = strtol(chunkSizeStr.c_str(), nullptr, 16);
        if (chunkSize == 0)
            break; // End of chunks

        pos = lineEnd + 2; // move past \r\n
        decoded += chunked.substring(pos, pos + chunkSize);
        pos += chunkSize + 2; // move past the chunk and its trailing \r\n
    }

    decoded.trim();
    return decoded;
}

String UtilsManager::extractJsonBody(const String &rawResponse)
{
    int bodyIndex = rawResponse.indexOf("\r\n\r\n"); // Find end of headers

    if (bodyIndex == -1)
    {
        Serial.println("No header-body separator found!");
        return "";
    }

    String body = rawResponse.substring(bodyIndex + 4); // Skip the "\r\n\r\n"
    body.trim();                                        // Clean up leading/trailing whitespace

    return body;
}

DynamicJsonDocument UtilsManager::parseJson(const String &json)
{
    DynamicJsonDocument doc(1024); // 1 KB buffer

    // Make a copy of the input json to avoid modifying the original constant reference
    String jsonCopy = json;
    jsonCopy = cleanJsonResponse(jsonCopy);

    DeserializationError error = deserializeJson(doc, jsonCopy);

    if (error)
    {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.f_str());

        setupRTCModule();
    }
    else
    {
        Serial.println("JSON parsed successfully!");
    }

    return doc;
}

String UtilsManager::cleanJsonResponse(String &response)
{
    // Remove random characters at the beginning
    while (response.length() > 0 && response[0] != '{')
    {
        response.remove(0, 1); // Remove first character until '{'
    }

    // Remove random characters at the end
    while (response.length() > 0 && response[response.length() - 1] != '}')
    {
        response.remove(response.length() - 1, 1); // Remove last character until '}'
    }

    return response;
}

void UtilsManager::getCurrentTime()
{
    RTCTime currentTime;
    RTC.getTime(currentTime);
    Serial.print(currentTime.getYear());
    Serial.print("-");
    Serial.print(Month2int(currentTime.getMonth()));
    Serial.print("-");
    Serial.print(currentTime.getDayOfMonth());
    Serial.print(" ");
    Serial.print(currentTime.getHour());
    Serial.print(":");
    Serial.print(currentTime.getMinutes());
    Serial.print(":");
    Serial.println(currentTime.getSeconds());
}