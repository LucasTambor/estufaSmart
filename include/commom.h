#ifndef _COMMOM_H_
#define _COMMOM_H_

#include <Arduino.h>


extern QueueHandle_t xCommandQueue;

extern SemaphoreHandle_t xWifiRssiMutex;
extern SemaphoreHandle_t xHorarioMutex;
extern SemaphoreHandle_t xWifiReadyMutex;

extern bool wifi_ready;
extern uint32_t rssi;

extern String horario;

//********************************************************************************************************
extern TaskHandle_t xTaskInputHandle,xTaskDisplayHandle, xTaskNTPHandle;

/* Protótipo das Tasks*/
extern void vTaskInput(void *pvParameters );
extern void vTaskNTP(void *pvParameters);
extern void vTaskDisplay(void *pvParameters);

#endif //_COMMOM_H_