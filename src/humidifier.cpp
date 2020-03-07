#include <Arduino.h>
#include "commom.h"
#include "humidifier.h"

void vTaskHumidifier(void *pvParameters) {
  (void) pvParameters;
  bool mode = 0;
  bool state = 0;

  // CONFIGURAÇAO PINO
  pinMode(PIN_HUMIDIFIER, OUTPUT);

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
        state = HumidifierAutomaticControl();
        break;
      case MANUAL_MODE:
        state = HumidifierManualControl();
        break;
      default:
      break;
    }

    digitalWrite(PIN_HUMIDIFIER, !state);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

bool HumidifierManualControl() {
  bool state = 0;

  xSemaphoreTake( xHumidifierMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  state = humidifier_state;
  xSemaphoreGive( xHumidifierMutex );

  return state;
}

bool HumidifierAutomaticControl() {
  bool state = 0;
  uint8_t internal_hum = 0;
  uint8_t internal_hum_set_point = 0;
  static uint8_t control = HUMIDIFIER_AUTOMATIC_IDLE;

  xSemaphoreTake( xHumiditySetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  internal_hum_set_point = humidity_set_point;
  xSemaphoreGive( xHumiditySetPointMutex );

  xSemaphoreTake( xHumidityMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  internal_hum = humidity_value;
  xSemaphoreGive( xHumidityMutex );

  switch(control) {
    case HUMIDIFIER_AUTOMATIC_IDLE:
      control = internal_hum <= internal_hum_set_point ? HUMIDIFIER_AUTOMATIC_ON : HUMIDIFIER_AUTOMATIC_OFF;
      state = 0;
      break;
    case HUMIDIFIER_AUTOMATIC_ON:
      if(internal_hum >= internal_hum_set_point + HUMIDIFIER_HISTERESIS) {
        control = HUMIDIFIER_AUTOMATIC_OFF;
      } else {
        control = HUMIDIFIER_AUTOMATIC_ON;
      }
      state = 1;
      break;
    case HUMIDIFIER_AUTOMATIC_OFF:
      if(internal_hum <= internal_hum_set_point - HUMIDIFIER_HISTERESIS) {
        control = HUMIDIFIER_AUTOMATIC_ON;
      } else {
        control = HUMIDIFIER_AUTOMATIC_OFF;
      }
      state = 0;
      break;
    default:
      control = HUMIDIFIER_AUTOMATIC_IDLE;
      break;
  }

  xSemaphoreTake( xHumidifierMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  humidifier_state = state;
  xSemaphoreGive( xHumidifierMutex );

  return state;
}
