#ifndef _FAN_H_
#define _FAN_H_

#define PIN_FAN   16
#define TEMPERATURE_HISTERESIS    1

enum {
  MOTOR_AUTOMATIC_IDLE = 0,
  MOTOR_AUTOMATIC_ON,
  MOTOR_AUTOMATIC_OFF,
};

bool FanAutomaticControl();
bool FanManualControl();
uint8_t GetDutyFromSpeed(uint8_t speed);

#endif // _FAN_H_