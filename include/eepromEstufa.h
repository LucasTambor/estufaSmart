#ifndef _EEPROM_ESTUFA_
#define _EEPROM_ESTUFA_

#define EEPROM_SIZE               128
#define OPERATION_MODE_ADDR      0
#define LIGHT_STATE_ADDR          2
#define LIGHT_SCHEDULE_ON_ADDR    4
#define LIGHT_SCHEDULE_OFF_ADDR   36
#define TEMP_SET_POINT_ADDR       70
#define HUMIDITY_SET_POINT_ADDR   72
#define MOTOR_SPEED_ADDR          74
#define MOTOR_STATE_ADDR          76
#define HUMIDIFIER_STATE_ADDR     78

#define MAX_STRING_SIZE           32

void initEeprom();
void initVarFromEeprom();

void saveToEeprom(uint8_t addr, uint8_t value);
void saveStringToEeprom(uint8_t addr, String string);
String readStringFromEeprom(uint8_t addr);
#endif //_EEPROM_ESTUFA_