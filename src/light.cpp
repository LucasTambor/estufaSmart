#include "commom.h"
#include "light.h"

void vTaskLight(void *pvParameters) {
  (void) pvParameters;
  bool mode = 0;
  bool state = 0;
  pinMode(PIN_LIGHT, OUTPUT);

  bool init_task = 0;
  while(!init_task) {
    xSemaphoreTake( xWifiReadyMutex, pdMS_TO_TICKS(200) );
    init_task = wifi_ready;
    xSemaphoreGive( xWifiReadyMutex );

    vTaskDelay(pdMS_TO_TICKS(500));
  }

  while(1) {
    xSemaphoreTake( xOpStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    mode = operation_state;
    xSemaphoreGive( xOpStateMutex );

    switch(mode) {
      case AUTOMATIC_MODE:
        state = LightAutomaticControl();
        break;
      case MANUAL_MODE:
        state = LightManualControl();
        break;
      default:
      break;
    }

    digitalWrite(PIN_LIGHT, state);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}


bool LightAutomaticControl() {
  String now;
  uint16_t now_int;
  uint16_t schedule_on_int = 0;
  uint16_t schedule_off_int = 0;
  bool state = 0;

  xSemaphoreTake( xHorarioMutex, portMAX_DELAY );
  now = horario;
  xSemaphoreGive( xHorarioMutex );

  now_int = getIntFromHour(now);
  schedule_on_int = getIntFromHour(schedule_light_ON);
  schedule_off_int = getIntFromHour(schedule_light_OFF);

  if(schedule_off_int > schedule_on_int) {
    if(schedule_on_int <= now_int &&  now_int < schedule_off_int) {
      state = 1;
    }else {
      state = 0;
    }
  }else {
    if(schedule_on_int <= now_int ||  now_int < schedule_off_int) {
      state = 1;
    }else {
      state = 0;
    }
  }

  xSemaphoreTake( xLightStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  light_state = state;
  xSemaphoreGive( xLightStateMutex );

  return state;
}

bool LightManualControl() {
  bool state = 0;

  xSemaphoreTake( xLightStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  state = light_state;
  xSemaphoreGive( xLightStateMutex );

  return state;
}

uint16_t getIntFromHour(String hour) {
  String tempHour = hour;
  tempHour.remove(2,1);
  String hourSub = tempHour.substring(0,4);
  return tempHour.toInt();
}