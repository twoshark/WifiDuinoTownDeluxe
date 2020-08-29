#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <string.h>

const String HOMIE_SAYS = "[homie says]: ";
//Who's really got your app? Your homie does.
class Homie
{
private:
  char _ssid[];
  uint32_t _ESP_ID;
  WiFiManager _WM;

public:
  Homie();
  void setup_ota();
  void handle_ota();
  void setup_wifi(char ssid[]);
  void log(int i);
  void log(char *s);
  void log(String s);
};