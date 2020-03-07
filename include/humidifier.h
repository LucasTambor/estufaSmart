#ifndef _HUMIDIFIER_H_
#define _HUMDIFIER_H_


#define PIN_HUMIDIFIER            19
#define HUMIDIFIER_HISTERESIS     2

enum {
  HUMIDIFIER_AUTOMATIC_IDLE = 0,
  HUMIDIFIER_AUTOMATIC_ON,
  HUMIDIFIER_AUTOMATIC_OFF,
};

bool HumidifierAutomaticControl();
bool HumidifierManualControl();

#endif // _HUMDIFIER_H_