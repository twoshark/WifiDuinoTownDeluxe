#define ARTNET_ENABLE_WIFI true

#include "../lib/homie.h";
#include "artnet/Artnet.h";
using namespace std;

//homie.
Homie homie; 
//Arturo, Artnet Specialist
ArtnetWiFiReceiver arturo; 

int universe = 1;

void pixelmap_receiver(uint8_t* data, uint16_t size)
{
  if (size % 3 != 0) {
    homie.log("Warning! Unexpected amount of data");
  }
  uint16_t pixels = size / 3;
  for (int i=0; i< pixels; i++ ) {
    char buf[16];
    sprintf(buf, "Pixel ID: %u", i);
    homie.log("Red:");
    sprintf(buf, "Green: %u", data[i * 3]);
    homie.log(buf);
    sprintf(buf, "Red: %u", data[i * 3 + 1]);
    homie.log(buf);
    sprintf(buf, "Blue: %u", data[i * 3 + 2]);
    homie.log(buf);
  }
}

void setup()
{
  homie.setup_wifi("Artnet Receiver");
  arturo.begin(); // Begin listening for ArtNet packets on default port
  arturo.subscribe(universe, pixelmap_receiver);
}

void loop(){
  //Serial.println("~*{:(~):}*~");
  arturo.parse();
  delay(100);
}