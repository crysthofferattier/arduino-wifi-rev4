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
    DynamicJsonDocument parseJson(String json);

private:
};

#endif