#include <Arduino.h>
#include <secrets.h>
#include <constants.h>

#include <WiFiS3.h>
#include "RTC.h"

bool DEBUG = true;

WiFiClient client;

int status = WL_IDLE_STATUS;

void connectToNetwork();
void printNetworkConnectionDetails();
void sendDataToServer();

void setUpRTCModule();

void debugMessage(String lvl, String msg);

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  connectToNetwork();
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  sendDataToServer();
}

void connectToNetwork()
{
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    while (true)
      ;
  }

  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SECRET_SSID);

    status = WiFi.begin(SECRET_SSID, SECRET_PASS);

    delay(5000);
  }

  printNetworkConnectionDetails();
}

void printNetworkConnectionDetails()
{
  Serial.print("SSID: ");
  Serial.println(SECRET_SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void sendDataToServer()
{
  if (client.connect(SERVER_ADDR, SERVER_PORT))
  {
    Serial.println("Connected to server");

    String jsonData = "{\"temp\":\"25.9\"}";

    // Make a HTTP request:
    client.println("POST /data HTTP/1.1");
    client.println("Host: arduinounorev4wifi.com");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(jsonData.length());
    client.println("Connection: close");
    client.println();
    client.println(jsonData); // body
    client.println();
  }
}

void setUpRTCModule()
{
  RTC.begin();

  RTCTime startTime(30, Month::JUNE, 2023, 13, 37, 00, DayOfWeek::WEDNESDAY, SaveLight::SAVING_TIME_ACTIVE);

  RTC.setTime(startTime);

  RTCTime currentTime;
  RTC.getTime(currentTime);

  Serial.println(currentTime.getUnixTime());
}

void getServerTimeStamp()
{
  if (client.connect(SERVER_ADDR, SERVER_PORT))
  {
    debugMessage(LOG_DEBUG, F("connected to server"));
    // Make a HTTP request:
    client.println("GET /timestamp HTTP/1.1");
    client.println("Host: arduinorev4wifi.com");
    client.println("Connection: close");
    client.println();
  }
}

void debugMessage(String lvl, String msg)
{
#ifdef DEBUG
  Serial.print(lvl);
  Serial.println(msg);
#endif
}