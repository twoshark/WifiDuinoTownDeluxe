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
  void log(String s) 
  {
    //make a log
    Serial.println(HOMIE_SAYS + s);
  }

  void log(char s[]){
    //My homie is a Lumberjack. homie makes Logs. 
    Serial.println(HOMIE_SAYS + String(s));
  }

public:
  Homie()
  {
    Serial.begin(115200);
    log("I am your homie. Let Us Begin.");
    this->_ESP_ID = ESP.getChipId();
    log("This is where we're at:");
    log("ESP8266 ID:");
    log(String(this->_ESP_ID));
  }

  void setup_ota()
  {
    // Define OTA Event Handlers
    ArduinoOTA.onStart([this]() {
      String type = ArduinoOTA.getCommand() == U_FLASH
                        ? "sketch"
                        : "filesystem";
      // NOTE: if updating FS this would be the place to unmount FS using FS.end()
      log("Start updating " + type);
    });
    ArduinoOTA.onEnd([this]() {
      log("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([this](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      switch (error)
      {
      case OTA_AUTH_ERROR:
        log("Auth Failed");
        break;
      case OTA_BEGIN_ERROR:
        log("Begin Failed");
        break;
      case OTA_CONNECT_ERROR:
        log("Connect Failed");
        break;
      case OTA_RECEIVE_ERROR:
        log("Receive Failed");
        break;
      case OTA_END_ERROR:
        log("End Failed");
        break;
      default:
        break;
      }
    });
    ArduinoOTA.begin();
    log("OTA Ready");
    log("IP address: ");
    log(WiFi.localIP().toString());
  }
  
  void handle_ota(){
    log("Begin Over the Air Update:");
    ArduinoOTA.handle();
    log("OTA Update Complete.");
  }

  void setup_wifi(char ssid[])
  {
    this->_WM.resetSettings();
    this->_WM.setTimeout(180); // 3min timeout

    // Create unique SSID
    char buf[16];
    sprintf(buf,  + "%s-%u", ssid, this->_ESP_ID);

    // Connect to WiFi, create AP if fails, reset if timeout
    if (!this->_WM.autoConnect(buf))
    {
      log("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      while (1)
        delay(1000);
    }
  }
};