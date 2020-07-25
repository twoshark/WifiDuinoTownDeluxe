#include "setup_util.h"

void setup() {
  SetupUtility setup_util;
  setup_util.Wifi();
  setup_util.Ota();
}
