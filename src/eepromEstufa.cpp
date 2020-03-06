#include <Arduino.h>
#include <EEPROM.h>
#include "commom.h"
#include "eepromEstufa.h"

void initEeprom() {
  EEPROM.begin(EEPROM_SIZE);
}


void initVarFromEeprom() {
  operation_state = EEPROM.read(OPERATION_STATE_ADDR);
  light_state = EEPROM.read(LIGHT_STATE_ADDR);
  schedule_light_ON = readStringFromEeprom(LIGHT_SCHEDULE_ON_ADDR);
  schedule_light_OFF = readStringFromEeprom(LIGHT_SCHEDULE_OFF_ADDR);
  temperature_set_point = EEPROM.read(TEMP_SET_POINT_ADDR);
  humidity_set_point = EEPROM.read(HUMIDITY_SET_POINT_ADDR);
  motor_speed = EEPROM.read(MOTOR_SPEED_ADDR);
  motor_state = EEPROM.read(MOTOR_STATE_ADDR);
}

void saveToEeprom(uint8_t addr, uint8_t value) {
  EEPROM.write(addr, value);
  EEPROM.commit();
}

void saveStringToEeprom(uint8_t addr, String string) {
  uint8_t i;
  for(i = 0; i<string.length(); i++)
  {
    EEPROM.write(addr+i, string[i]);
  }
  EEPROM.write(addr+string.length(), '\0');   //Add termination null character for String Data
  EEPROM.commit();
}

String readStringFromEeprom(uint8_t addr) {
  char data[MAX_STRING_SIZE];
  uint8_t len=0;
  uint8_t k;
  k = EEPROM.read(addr);
  while(k != '\0' && len < MAX_STRING_SIZE)   //Read until null character
  {
    k = EEPROM.read(addr + len);
    data[len] = k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

