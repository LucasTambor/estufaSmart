#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Arduino.h>

#define PIN_LIGHT   23

bool LightAutomaticControl();
bool LightManualControl();
uint16_t getIntFromHour(String hour);

#endif // _LIGHT_H_