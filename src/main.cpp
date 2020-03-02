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

// Configurações do WiFi
const char* ssid     = "badDaysSpaceship2"; // Nome da rede WiFi
const char* password = "+ps3=dw71102"; // Senha da rede WiFi

// Configurações do Servidor NTP
const char* servidorNTP = "a.st1.ntp.br"; // Servidor NTP para pesquisar a hora
const int fusoHorario = -10800; // Fuso horário em segundos (-03h = -10800 seg)
const int taxaDeAtualizacao = 1800000; // Taxa de atualização do servidor NTP em milisegundos

WiFiUDP ntpUDP; // Declaração do Protocolo UDP
NTPClient timeClient(ntpUDP, servidorNTP, fusoHorario, 60000);

//**********************************************************************************************************
TaskHandle_t xTaskInputHandle,xTaskDisplayHandle, xTaskNTPHandle;

QueueHandle_t xCommandQueue;

SemaphoreHandle_t xWifiRssiMutex;
SemaphoreHandle_t xHorarioMutex;
SemaphoreHandle_t xWifiReadyMutex;

bool wifi_ready = 0;
uint32_t rssi = 0;

String horario;

void setup()
{
  // Declarar Serial para realizar debug do código
  Serial.begin(115200);
  delay(10);

  xCommandQueue = xQueueCreate(5, sizeof(char));

  xWifiReadyMutex = xSemaphoreCreateMutex();
  xHorarioMutex = xSemaphoreCreateMutex();
  xWifiRssiMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(vTaskNTP,  "TaskNTP",  configMINIMAL_STACK_SIZE + 2048,  NULL,  1,  &xTaskNTPHandle, PRO_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskDisplay,  "TaskDisplay",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskDisplayHandle, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskInput,  "TaskInput",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskInputHandle, APP_CPU_NUM);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}

//***************************************************************************************************************************



//***************************************************************************************************************************

void vTaskNTP(void *pvParameters) {
  (void) pvParameters;

  // Conectar ao WiFi
  WiFi.begin(ssid, password);

  // Aguardando conexão do WiFi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  Serial.println("");
  Serial.print("WiFi conectado. Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Iniciar cliente de aquisição do tempo
  timeClient.begin();

  xSemaphoreTake( xWifiReadyMutex, portMAX_DELAY );
  wifi_ready = 1;
  xSemaphoreGive( xWifiReadyMutex );

  while(1) {
    timeClient.update();

    xSemaphoreTake( xHorarioMutex, portMAX_DELAY );
    horario = timeClient.getFormattedTime();
    xSemaphoreGive( xHorarioMutex );

    xSemaphoreTake( xWifiRssiMutex, portMAX_DELAY );
    rssi = WiFi.RSSI();
    xSemaphoreGive( xWifiRssiMutex );

    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

//***************************************************************************************************************************

