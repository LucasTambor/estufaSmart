#ifndef _COMMOM_H_
#define _COMMOM_H_

#include <Arduino.h>

#define WIFI_SSID       "badDaysSpaceship2"
#define WIFI_PASSWORD   "+ps3=dw71102"

extern QueueHandle_t xCommandQueue;

extern SemaphoreHandle_t xWifiRssiMutex;
extern SemaphoreHandle_t xHorarioMutex;
extern SemaphoreHandle_t xWifiReadyMutex;
extern SemaphoreHandle_t xWifiMutex;

extern SemaphoreHandle_t xOpStateMutex;
extern SemaphoreHandle_t xLightStateMutex;

extern bool wifi_ready;
extern uint32_t rssi;

extern String horario;

//********************************************************************************************************

extern bool mqttState;

extern bool operation_state;
extern bool light_state;
extern String schedule_light_ON;
extern String schedule_light_OFF;

//********************************************************************************************************

extern TaskHandle_t xTaskInputHandle,xTaskDisplayHandle, xTaskNTPHandle, xTaskMqttHandle;

/* Protótipo das Tasks*/
extern void vTaskInput(void *pvParameters );
extern void vTaskNTP(void *pvParameters);
extern void vTaskDisplay(void *pvParameters);
extern void vTaskMqtt(void *pvParameters);

#endif //_COMMOM_H_