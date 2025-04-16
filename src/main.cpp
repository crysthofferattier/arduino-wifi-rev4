#include <Arduino.h>
#include <network/NetworkManager.h>
#include <client/ClientManager.h>
#include <utils/UtilsManager.h>
#include <debug/DebugManager.h>
#include <secrets.h>
#include <constants.h>

#include "RTC.h"

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  debugManager.debugMessage(debugManager.LOG_INFO, "Setting Up.");
  pinMode(LED_BUILTIN, OUTPUT);

  networkManager.connect();

  if (networkManager.isConnected())
    networkManager.showNetworkInfo();

  utilsManager.setupRTCModule();
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  debugManager.debugMessage(debugManager.LOG_INFO, "LED...");

  utilsManager.getCurrentTime();
}