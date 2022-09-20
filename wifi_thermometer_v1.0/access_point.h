#ifndef access_point_h
#define access_point_h
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include "LittleFS.h"
#include "pag1.h"
#include "pag2.h"
#include "pag_info.h"
#include "notfound_pag.h"

const char* ap_ssid = "WiFi Thermometer";
const char* ap_password = "12345678";

const byte DNS_PORT = 53;
IPAddress apIP(192,168,1,1);
DNSServer dnsServer;
ESP8266WebServer server(80);

extern bool ap_mode;

void create_ap();
void handleconf();
void handleNotFound();
void handlesave();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void handleconf() {
  server.send(200, "text/html", pag1);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void handleinfo() {
  server.send(200, "text/html", pag_info);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void handleNotFound() {
  server.send(404, "text/html", notfound_pag);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void handlesave() {
  String str = "";

  if (server.args() > 0 ) {
    for ( uint8_t i = 0; i < 3; i++ ) {
      str += server.argName(i) + " = " + server.arg(i) + "\r\n";

      if ( i == 0) {
        File ssid_file = LittleFS.open(F("/ssid.txt"), "w");
        ssid_file.print(server.arg(i));
        ssid_file.close();
      }

      else if ( i == 1) {
        File pssw_file = LittleFS.open(F("/pssw.txt"), "w");
        pssw_file.print(server.arg(i));
        pssw_file.close();
      }

      else if (i == 2) {
        File nome_file = LittleFS.open(F("/nome.txt"), "w");
        nome_file.print(server.arg(i));
        nome_file.close();
      }
    }
  }
  server.send(200, "text/html", pag2);
  delay(1000);
  ESP.restart() ;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void create_ap() {
  ap_mode = true;
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));
  WiFi.softAP(ap_ssid, ap_password);
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_PORT, "www.wifithermometer.com", apIP);
  //server.on("/conf", handleconf );
  server.on("/", handleconf );
  server.on("/save", handlesave);
  server.on("/info", handleinfo);
  server.onNotFound(handleNotFound);
  server.begin();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif
