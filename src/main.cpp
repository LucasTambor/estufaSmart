#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "commom.h"
#include "display.h"
#include "input.h"
#include "ntp.h"
#include "mqtt.h"
#include "light.h"

//**********************************************************************************************************

QueueHandle_t xCommandQueue;

TaskHandle_t xTaskInputHandle;
TaskHandle_t xTaskDisplayHandle;
TaskHandle_t xTaskNTPHandle;
TaskHandle_t xTaskMqttHandle;
TaskHandle_t xTaskLightHandle;

SemaphoreHandle_t xWifiRssiMutex;
SemaphoreHandle_t xHorarioMutex;
SemaphoreHandle_t xWifiReadyMutex;
SemaphoreHandle_t xWifiMutex;
SemaphoreHandle_t xOpStateMutex;
SemaphoreHandle_t xLightStateMutex;
SemaphoreHandle_t xLightScheduleMutex;

bool wifi_ready = 0;
uint32_t rssi = 0;





void setup()
{
  // Declarar Serial para realizar debug do código
  Serial.begin(115200);
  delay(10);

  xCommandQueue = xQueueCreate(5, sizeof(char));

  xWifiReadyMutex = xSemaphoreCreateMutex();
  xHorarioMutex = xSemaphoreCreateMutex();
  xWifiRssiMutex = xSemaphoreCreateMutex();
  xWifiReadyMutex = xSemaphoreCreateMutex();
  xOpStateMutex = xSemaphoreCreateMutex();
  xLightStateMutex = xSemaphoreCreateMutex();
  xLightScheduleMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(vTaskNTP,  "TaskNTP",  configMINIMAL_STACK_SIZE + 2048,  NULL,  1,  &xTaskNTPHandle, PRO_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskMqtt,  "TaskMqtt",  configMINIMAL_STACK_SIZE + 4096,  NULL,  2,  &xTaskMqttHandle, PRO_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskDisplay,  "TaskDisplay",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskDisplayHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskInput,  "TaskInput",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskInputHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskLight,  "TaskLight",  configMINIMAL_STACK_SIZE + 512,  NULL,  2,  &xTaskLightHandle, APP_CPU_NUM);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}

