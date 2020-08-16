#include "homie.h"

//homie.
Homie homie; 

void setup()
{
  homie.setup_wifi("Model Home Tour");
  homie.setup_ota();
}

void loop(){
  Serial.println("Hearbeat!");
  homie.handle_ota();
}
