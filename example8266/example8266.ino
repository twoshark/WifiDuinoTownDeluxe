#include "homie.h"

//homie.
Homie homie;

void setup()
{
  homie.setup_wifi("WiFi Duino Town Deluxe Model Home Tour");
  homie.setup_ota();
}

void loop(){
  homie.handle_ota();
}
