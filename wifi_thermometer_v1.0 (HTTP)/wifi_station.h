#ifndef wifi_station_h
#define wifi_station_h
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "LittleFS.h"
#include "Arduino.h"

extern char text[];
extern bool ap_mode;
extern const int resetpin;
extern const int ledpin;

String ssid = "";
String password = "";
String nome = "";
String nome2 = "";

ESP8266WebServer webserver(80);

void connect_to_network();
void submit_data();
void run_sta_wifi();
void read_conf();
void read_temp();
void conf_reset();
void connection_blink();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void read_conf()
{
  File ssid_file = LittleFS.open(F("/ssid.txt"), "r");
  ssid = ssid_file.readString();
  ssid_file.close();
  File pssw_file = LittleFS.open(F("/pssw.txt"), "r");
  password = pssw_file.readString();
  pssw_file.close();
  File nome_file = LittleFS.open(F("/nome.txt"), "r");
  nome = nome_file.readString();
  nome2 = nome;
  nome.replace(" ", "");
  nome_file.close();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void submit_data()
{
  read_temp();
  webserver.send(200, "text/plain", text);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void connect_to_network()
{
  read_conf();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (true)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      break;
    }
    conf_reset();
    connection_blink();
  }
  if (MDNS.begin(nome))
  {
  }
  webserver.on("/read", submit_data);
  webserver.begin();
  digitalWrite(ledpin, LOW);
  ap_mode = false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif
