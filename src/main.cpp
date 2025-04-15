#include <Arduino.h>
#include <network/NetworkManager.h>
#include <client/ClientManager.h>
#include <utils/UtilsManager.h>
#include <secrets.h>
#include <constants.h>

#include "RTC.h"

NetworkManager networkManager(SECRET_SSID, SECRET_PASS);

ClientManager clientManager;
UtilsManager utilsManager;

void sendDataToServer();

void setUpRTCModule();

void setup()
{
  Serial.begin(9600);
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

  utilsManager.getCurrentTime();
}