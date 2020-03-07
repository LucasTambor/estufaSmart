#include <Arduino.h>
#include "commom.h"
#include "fan.h"

// PROGRAMAÇÃO PWM
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void vTaskFan(void *pvParameters) {
  (void) pvParameters;
  bool mode = 0;
  bool state = 0;

  // CONFIGURAÇAO PWM MOTOR
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(PIN_FAN, ledChannel);

  // Aguarda a inicializacao do wifi
  bool init_task = 0;
  while(!init_task) {
    xSemaphoreTake( xWifiReadyMutex, pdMS_TO_TICKS(200) );
    init_task = wifi_ready;
    xSemaphoreGive( xWifiReadyMutex );

    vTaskDelay(pdMS_TO_TICKS(500));
  }

  while(1) {
    xSemaphoreTake( xOpStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    mode = operation_mode;
    xSemaphoreGive( xOpStateMutex );

    switch(mode) {
      case AUTOMATIC_MODE:
        state = FanAutomaticControl();
        break;
      case MANUAL_MODE:
        state = FanManualControl();
        break;
      default:
      break;
    }

    xSemaphoreTake( xMotorSpeedMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    uint8_t duty_cycle = state ? GetDutyFromSpeed(motor_speed) : 0;
    xSemaphoreGive( xMotorSpeedMutex );
    ledcWrite(ledChannel, duty_cycle);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

bool FanAutomaticControl() {
  bool state = 0;
  float internal_temp = 0;
  uint8_t internal_temp_set_point = 0;
  static uint8_t control = MOTOR_AUTOMATIC_IDLE;

  xSemaphoreTake( xTemperatureSetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  internal_temp_set_point = temperature_set_point;
  xSemaphoreGive( xTemperatureSetPointMutex );

  xSemaphoreTake( xTemperatureMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  internal_temp = temperature_value;
  xSemaphoreGive( xTemperatureMutex );

  switch(control) {
    case MOTOR_AUTOMATIC_IDLE:
      control = internal_temp >= internal_temp_set_point ? MOTOR_AUTOMATIC_ON : MOTOR_AUTOMATIC_OFF;
      state = 0;
      break;
    case MOTOR_AUTOMATIC_ON:
      if(internal_temp <= internal_temp_set_point - TEMPERATURE_HISTERESIS) {
        control = MOTOR_AUTOMATIC_OFF;
      } else {
        control = MOTOR_AUTOMATIC_ON;
      }
      state = 1;
      break;
    case MOTOR_AUTOMATIC_OFF:
      if(internal_temp >= internal_temp_set_point + TEMPERATURE_HISTERESIS) {
        control = MOTOR_AUTOMATIC_ON;
      } else {
        control = MOTOR_AUTOMATIC_OFF;
      }
      state = 0;
      break;
    default:
      control = MOTOR_AUTOMATIC_IDLE;
      break;
  }

  xSemaphoreTake( xMotorStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  motor_state = state;
  xSemaphoreGive( xMotorStateMutex );

  return state;
}

bool FanManualControl() {
  bool state = 0;

  xSemaphoreTake( xMotorStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  state = motor_state;
  xSemaphoreGive( xMotorStateMutex );

  return state;
}

uint8_t GetDutyFromSpeed(uint8_t speed) {
  return (uint8_t) pow(2,resolution) * ((float)speed / 100);
}
