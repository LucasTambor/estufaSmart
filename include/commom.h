#ifndef _COMMOM_H_
#define _COMMOM_H_

#include <Arduino.h>
#include "wifi_psw.h"

extern QueueHandle_t xCommandQueue;

extern SemaphoreHandle_t xWifiRssiMutex;
extern SemaphoreHandle_t xHorarioMutex;
extern SemaphoreHandle_t xWifiReadyMutex;
extern SemaphoreHandle_t xWifiMutex;

extern SemaphoreHandle_t xOpStateMutex;
extern SemaphoreHandle_t xLightStateMutex;
extern SemaphoreHandle_t xLightScheduleMutex;
extern SemaphoreHandle_t xTemperatureSetPointMutex;
extern SemaphoreHandle_t xHumiditySetPointMutex;
extern SemaphoreHandle_t xMotorSpeedMutex;
extern SemaphoreHandle_t xMotorStateMutex;
extern SemaphoreHandle_t xTemperatureMutex;
extern SemaphoreHandle_t xHumidityMutex;

extern bool wifi_ready;
extern uint32_t rssi;

extern String horario;

//********************************************************************************************************

extern bool mqttState;

extern bool operation_mode;
extern bool light_state;
extern bool motor_state;
extern String schedule_light_ON;
extern String schedule_light_OFF;
extern uint8_t temperature_set_point;
extern uint8_t humidity_set_point;
extern uint8_t motor_speed;
extern float temperature_value;
extern uint8_t humidity_value;

//********************************************************************************************************

extern TaskHandle_t xTaskInputHandle,xTaskDisplayHandle, xTaskNTPHandle, xTaskMqttHandle, xTaskDHTHandle;

/* Protótipo das Tasks*/
extern void vTaskInput(void *pvParameters );
extern void vTaskNTP(void *pvParameters);
extern void vTaskDisplay(void *pvParameters);
extern void vTaskMqtt(void *pvParameters);
extern void vTaskLight(void *pvParameters);
extern void vTaskDHT(void *pvParameters);


//********************************************************************************************************
//Operation Mode
enum {
  AUTOMATIC_MODE = 0,
  MANUAL_MODE
};


#endif //_COMMOM_H_