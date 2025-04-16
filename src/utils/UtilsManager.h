#ifndef UTILS_MANAGER_H
#define UTILS_MANAGER_H

#include <Arduino.h>
#include <RTC.h>
#include <ArduinoJson.h>

class UtilsManager
{
public:
    UtilsManager();

    void setupRTCModule();
    void getCurrentTime();
    DynamicJsonDocument parseJson(const String& json);
    String cleanJsonResponse(String& json);
    String extractJsonFromChunkedResponse(const String &rawResponse);
    String extractJsonBody(const String &rawResponse);


private:
};

#endif