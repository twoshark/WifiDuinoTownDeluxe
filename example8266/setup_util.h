#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

class SetupUtility
{
private:
  uint32_t _ESP_ID;

public:
  SetupUtility(){
    Serial.println("Booting...");
    this->_ESP_ID = ESP.getChipId();
    Serial.print("ESP8266 ID:");
    Serial.println(this->_ESP_ID);
  }
  
  void Ota()
  {
    // OTA things
    ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
      {
        type = "sketch";
      }
      else
      { // U_FS
        type = "filesystem";
      }
      // NOTE: if updating FS this would be the place to unmount FS using FS.end()
      Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR)
      {
        Serial.println("Auth Failed");
      }
      else if (error == OTA_BEGIN_ERROR)
      {
        Serial.println("Begin Failed");
      }
      else if (error == OTA_CONNECT_ERROR)
      {
        Serial.println("Connect Failed");
      }
      else if (error == OTA_RECEIVE_ERROR)
      {
        Serial.println("Receive Failed");
      }
      else if (error == OTA_END_ERROR)
      {
        Serial.println("End Failed");
      }
    });
    ArduinoOTA.begin();
    Serial.println("OTA Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  void Wifi()
  {
    WiFiManager wifiManager;
    //wifiManager.resetSettings();
    wifiManager.setTimeout(180); // 3min timeout

    // Create unique SSID
    char buf[16];
    sprintf(buf, "Frame-AP-%u", this->_ESP_ID);

    // Connect to WiFi, create AP if fails, reset if timeout
    if (!wifiManager.autoConnect(buf))
    {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      while (1)
        ;
    }
  }
};