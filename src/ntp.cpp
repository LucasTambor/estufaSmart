#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "commom.h"
#include "ntp.h"

// Configurações do Servidor NTP
const char* servidorNTP = "a.st1.ntp.br"; // Servidor NTP para pesquisar a hora
const int fusoHorario = -10800; // Fuso horário em segundos (-03h = -10800 seg)
const int taxaDeAtualizacao = 1800000; // Taxa de atualização do servidor NTP em milisegundos

WiFiUDP ntpUDP; // Declaração do Protocolo UDP
NTPClient timeClient(ntpUDP, servidorNTP, fusoHorario, 60000);

String horario;

void vTaskNTP(void *pvParameters) {
  (void) pvParameters;

  // Conectar ao WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

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
