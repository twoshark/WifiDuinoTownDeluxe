#include "homie.h"
#include <Artnet.h>

//homie.
Homie homie; 
//Arturo, Artnet Specialist
ArtnetWifiReceiver arturo;

int universe = 1;

void pixelmap_receiver(uint8_t* data, uint16_t size)
{
  if (size % 3 != 0) {
    homie.log("Warning! Unexpected amount of data");
  }
  uint16_t pixels = size / 3;

}

void setup()
{
  homie.setup_wifi("Artnet Rcv Example");
  arturo.begin(); // Begin listening for ArtNet packets on default port
  arturo.subscribe(universe, pixelmap_receiver);
}

void loop(){
  Serial.println("~*{:(~):}*~");
  arturo.parse();
}