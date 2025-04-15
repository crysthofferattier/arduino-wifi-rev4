#include <utils/UtilsManager.h>
#include <client/ClientManager.h>
#include <ArduinoJson.h>

#include <RTC.h>

UtilsManager::UtilsManager() {};

void UtilsManager::setupRTCModule()
{
    RTC.begin();

    // Get the raw JSON response as a string
    String jsonResponse = clientManager.get("/api/time/current/zone?timeZone=Europe%2FDublin", "timeapi.io", 443);

    // Parse the JSON response into a DynamicJsonDocument
    DynamicJsonDocument jsonObj = parseJson(jsonResponse);

    long timestamp = jsonObj["dateTime"];

    Serial.println("timestamp");
    Serial.println(timestamp);

    RTCTime timeToSet = timestamp;
    RTC.setTime(timeToSet);
}

DynamicJsonDocument UtilsManager::parseJson(const String& json) {
    DynamicJsonDocument doc(1024); // 1 KB buffer

// Make a copy of the input json to avoid modifying the original constant reference
    String jsonCopy = json;
    jsonCopy = cleanJsonResponse(jsonCopy);

    DeserializationError error = deserializeJson(doc, jsonCopy);

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.f_str());

        setupRTCModule();
    } else {
        Serial.println("JSON parsed successfully!");
    }

    return doc;
}

String UtilsManager::cleanJsonResponse(String& response) {
    // Remove random characters at the beginning
    while (response.length() > 0 && response[0] != '{') {
        response.remove(0, 1);  // Remove first character until '{'
    }

    // Remove random characters at the end
    while (response.length() > 0 && response[response.length() - 1] != '}') {
        response.remove(response.length() - 1, 1);  // Remove last character until '}'
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