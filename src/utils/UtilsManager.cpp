#include <utils/UtilsManager.h>
#include <client/ClientManager.h>
#include <ArduinoJson.h>

#include <RTC.h>

UtilsManager::UtilsManager() {};

void UtilsManager::setupRTCModule()
{
    RTC.begin();

    DynamicJsonDocument jsonObj = parseJson(clientManager.get("api/time/current/zone?timeZone=Europe%2FDublin", "https://timeapi.io", 443));

    long timestamp = jsonObj["timestamp"];

    RTCTime timeToSet = timestamp;
    RTC.setTime(timeToSet);

    Serial.println(timestamp);
}

DynamicJsonDocument UtilsManager::parseJson(String json){
    DynamicJsonDocument doc(1024); // 1 KB buffer

    // Parse the JSON response
    DeserializationError error = deserializeJson(doc, json);

    if (error)
    {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.f_str());
    }

    return doc;
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