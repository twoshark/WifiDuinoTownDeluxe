#include "homey.h"


//homey.
Homey homey;

void setup()
{
  homey.setup_wifi();
  homey.setup_ota();
}

void loop(){}
