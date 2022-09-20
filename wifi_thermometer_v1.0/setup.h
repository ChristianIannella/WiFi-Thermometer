#ifndef setup_h
#define setup_h
#include "Arduino.h"
#include "LittleFS.h"
#include "wifi_station.h"
#include "access_point.h"

void check_config();

void check_config()
{
  LittleFS.begin();
  File ssid_file = LittleFS.open(F("/ssid.txt"), "r");
  if (ssid_file)
  {
    if (ssid_file.readString() != "")
    {
      connect_to_network();
    }
    ssid_file.close();
  }
  else
  {
    create_ap();
  }
}

#endif
