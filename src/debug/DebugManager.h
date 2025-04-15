#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <Arduino.h>

class DebugManager
{
public:
    String LOG_INFO = "[INFO]";
    String LOG_ERROR = "[ERROR] ";
    String LOG_DEBUG = "[DEBUG] ";
    
    DebugManager();

    void debugMessage(String lvl, String msg);
};
#endif