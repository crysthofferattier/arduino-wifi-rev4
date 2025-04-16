#include <Arduino.h>
#include <debug/DebugManager.h>
#include <constants.h>

DebugManager::DebugManager() {};

DebugManager debugManager;

void DebugManager::debugMessage(String lvl, String msg)
{
#ifdef DEBUG
    Serial.print(lvl);
    Serial.print(" ");
    Serial.println(msg);
#endif
}