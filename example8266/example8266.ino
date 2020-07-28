#include "homey.h"

//homey.
Homey homey;

void setup()
{
  homey.setup_wifi("WiFi Duino Town Deluxe Model Home Tour");
  homey.setup_ota();
}

void loop(){
  homey.handle_ota();
}
