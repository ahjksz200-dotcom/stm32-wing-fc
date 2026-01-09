#include "config.h"

void setup() {
    initPins();
    imuInit();
    rcInit();
    gpsInit();
    compassInit();
    ekfInit();
    outputInit();
}

void loop() {
    rcUpdate();
    imuUpdate();
    ekfUpdate();
    navigationUpdate();
    failsafeUpdate();
    mixerUpdate();
    outputUpdate();
}
