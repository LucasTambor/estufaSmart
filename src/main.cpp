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
#include "eepromEstufa.h"
#include "dht.h"

//**********************************************************************************************************

QueueHandle_t xCommandQueue;

TaskHandle_t xTaskInputHandle;
TaskHandle_t xTaskDisplayHandle;
TaskHandle_t xTaskNTPHandle;
TaskHandle_t xTaskMqttHandle;
TaskHandle_t xTaskLightHandle;
TaskHandle_t xTaskDHTHandle;
TaskHandle_t xTaskFanHandle;
TaskHandle_t xTaskHumidifierHandle;

SemaphoreHandle_t xWifiRssiMutex;
SemaphoreHandle_t xHorarioMutex;
SemaphoreHandle_t xWifiReadyMutex;
SemaphoreHandle_t xWifiMutex;
SemaphoreHandle_t xOpStateMutex;
SemaphoreHandle_t xLightStateMutex;
SemaphoreHandle_t xLightScheduleMutex;
SemaphoreHandle_t xTemperatureSetPointMutex;
SemaphoreHandle_t xHumiditySetPointMutex;
SemaphoreHandle_t xMotorSpeedMutex;
SemaphoreHandle_t xMotorStateMutex;
SemaphoreHandle_t xTemperatureMutex;
SemaphoreHandle_t xHumidityMutex;
SemaphoreHandle_t xHumidifierMutex;

bool wifi_ready = 0;
uint32_t rssi = 0;

void setup()
{
  // Declarar Serial para realizar debug do código
  Serial.begin(115200);
  delay(10);

  initEeprom();
  initVarFromEeprom();

  xCommandQueue = xQueueCreate(5, sizeof(char));

  xWifiReadyMutex = xSemaphoreCreateMutex();
  xHorarioMutex = xSemaphoreCreateMutex();
  xWifiRssiMutex = xSemaphoreCreateMutex();
  xWifiReadyMutex = xSemaphoreCreateMutex();
  xOpStateMutex = xSemaphoreCreateMutex();
  xLightStateMutex = xSemaphoreCreateMutex();
  xLightScheduleMutex = xSemaphoreCreateMutex();
  xTemperatureSetPointMutex = xSemaphoreCreateMutex();
  xHumiditySetPointMutex = xSemaphoreCreateMutex();
  xMotorSpeedMutex = xSemaphoreCreateMutex();
  xMotorStateMutex = xSemaphoreCreateMutex();
  xTemperatureMutex = xSemaphoreCreateMutex();
  xHumidityMutex = xSemaphoreCreateMutex();
  xHumidifierMutex = xSemaphoreCreateMutex();

  //Core 0
  xTaskCreatePinnedToCore(vTaskNTP,  "TaskNTP",  configMINIMAL_STACK_SIZE + 2048,  NULL,  1,  &xTaskNTPHandle, PRO_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskMqtt,  "TaskMqtt",  configMINIMAL_STACK_SIZE + 4096,  NULL,  2,  &xTaskMqttHandle, PRO_CPU_NUM);

  //Core 1
  xTaskCreatePinnedToCore(vTaskDisplay,  "TaskDisplay",  configMINIMAL_STACK_SIZE + 2048,  NULL,  1,  &xTaskDisplayHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskInput,  "TaskInput",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskInputHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskLight,  "TaskLight",  configMINIMAL_STACK_SIZE + 512,  NULL,  2,  &xTaskLightHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskDHT,  "TaskDHT",  configMINIMAL_STACK_SIZE + 512,  NULL,  3,  &xTaskDHTHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskFan,  "TaskFan",  configMINIMAL_STACK_SIZE + 512,  NULL,  3,  &xTaskFanHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskHumidifier,  "TaskHumidifier",  configMINIMAL_STACK_SIZE + 512,  NULL,  3,  &xTaskHumidifierHandle, APP_CPU_NUM);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}

