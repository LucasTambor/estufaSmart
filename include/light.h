#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Arduino.h>

#define PIN_LIGHT   23

enum Mode_e {
  AUTOMATIC_MODE = 0,
  MANUAL_MODE
};

bool LightAutomaticControl();
bool LightManualControl();
uint16_t getIntFromHour(String hour);

#endif // _LIGHT_H_