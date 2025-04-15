#include <Arduino.h>
#include <debug/DebugManager.h>
#include <constants.h>

DebugManager::DebugManager(){};

void DebugManager::debugMessage(String lvl, String msg)
{
#ifdef DEBUG
    Serial.print(lvl);
    Serial.println(msg);
#endif
}