#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdio.h>

// Configuração do Display OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

enum {
  DISPLAY_HOME = 0,
  DISPLAY_LIGHT_MENU,
  DISPLAY_LIGHT_ON_CONF,
  DISPLAY_LIGHT_OFF_CONF,
  DISPLAY_SET_POINT_MENU,
  DISPLAY_SET_POINT_TEMPERATURE_CONF,
  DISPLAY_SET_POINT_HUMIDITY_CONF,
  DISPLAY_MOTOR_MENU,
  DISPLAY_MOTOR_SPEED_CONF,
  DISPLAY_OPERATION_MODE_CONF,
};


//**********************************************************************************************************

void setWifiIcon(int32_t rssi);
void setMqttIcon(bool state);
void setLighIcon(bool state);
void setMotorIcon(bool state);
void setHumidifierIcon(bool state);

void DisplayControl(char command);
uint8_t displayHomeState(char command);
uint8_t displaylighMenuState(char command);
uint8_t displayLightOnConfState(char command);
uint8_t displayLightOFFConfState(char command);
uint8_t displaySetPointMenuState(char command);
uint8_t displaySetPointTemperatureConfState(char command);
uint8_t displaySetPointHumidityConfState(char command);
uint8_t displayMotorMenuState(char command);
uint8_t displayMotorSpeedMenuState(char command);
uint8_t displayOperationModeState(char command);

#endif //_DISPLAY_H