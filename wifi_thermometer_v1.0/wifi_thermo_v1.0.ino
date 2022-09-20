#include "Arduino.h"
#include <Wire.h>
#include "SparkFunHTU21D.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "setup.h"
#include "pag1.h"
#include "pag2.h"
#include "pag_info.h"
#include "wifi_station.h"

HTU21D myHumidity;

bool ap_mode = false;
const int ledpin = 2;
const int resetpin = 16;
unsigned long previousMillis = 0;
const long interval_ap = 1500;
const long interval_connection = 500;

char text[] = "    ";

void setup()
{
  pinMode(resetpin, INPUT_PULLUP);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, HIGH);
  myHumidity.begin();
  delay(500);
  check_config();
}

void loop()
{
  dnsServer.processNextRequest();
  MDNS.update();
  server.handleClient();
  webserver.handleClient();
  ap_blink();
  conf_reset();
}

void read_temp()
{
  int h = myHumidity.readHumidity();
  int t = myHumidity.readTemperature();

  sprintf(text, (PGM_P)F("%02d-%02d"), t, h);
}

void ap_blink()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval_ap)
  {
    previousMillis = currentMillis;
    if (ap_mode == true)
    {
      digitalWrite(ledpin, LOW);
      delay(10);
    }
  }
  if (ap_mode == true)
  {
    digitalWrite(ledpin, HIGH);
  }
}

void connection_blink()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval_connection)
  {
    previousMillis = currentMillis;
    digitalWrite(ledpin, LOW);
    delay(10);
    digitalWrite(ledpin, HIGH);
  }
}

void conf_reset()
{
  if (digitalRead(resetpin) == LOW)
  {
    for (int i = 0; i <= 10; i++)
    {
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      delay(50);
    }
    LittleFS.format();
    ESP.restart();
  }
}
