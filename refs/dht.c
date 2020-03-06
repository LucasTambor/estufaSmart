/*
    ATIVIDADE FINAL - ESTUFA SMART
    CAIUBI E LUCAS
*/

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <PubSubClient.h>


/* Variáveis para armazenar o handle da Task */
 TaskHandle_t xTaskDHTHandle,xTaskPrintHandle;

/* Defines */
#define LED 2
#define DHTPIN            4 
#define DHTTYPE   DHT22

/* Protótipo das Tasks*/
 void vTaskDHT(void *pvParameters);
//  void vTaskMQTT(void *pvParameters);
 
// void vTaskPrint(void *pvParameters);

/* CONECTANDO DHT*/
DHT_Unified dht(DHTPIN, DHTTYPE);

/* CONECTANDO WIFI E CLIENT*/
// WiFiClient espClient;
// PubSubClient client(espClient);

/* configuraçãoes da REDE e broker MQTT*/
// const char* ssid = "chico";
// const char* password =  "131006vs";
// const char* mqttServer = "m16.cloudmqtt.com";
// const int mqttPort = 12373;
// const char* mqttUser = "xqumjdws";
// const char* mqttPassword = "LUCAdqPeU7MQ";

/* Funções auxiliares */
void vInitHW(void);

//função pra reconectar ao servido MQTT
// void reconect() {
//   //Enquanto estiver desconectado
//   while (!client.connected()) {

//      if (client.connect("ESP32Client", mqttUser, mqttPassword ))
//     {
//       Serial.println("Conectado ao broker!");
//     }
//     else
//     {
//       Serial.print("Falha na conexao ao broker - Estado: ");
//       Serial.print(client.state());
//       vTaskDelay(pdMS_TO_TICKS(100));
//     }
//   }
// }

void setup() {
  vInitHW();
    /* Cria a vTaskDHT */
  xTaskCreatePinnedToCore(vTaskDHT,
    "TaskDHT",
    configMINIMAL_STACK_SIZE + 1024,
    NULL,
    2,
    &xTaskDHTHandle,
    APP_CPU_NUM);   
  /* Cria a vTaskPrint */
  //xTaskCreatePinnedToCore(vTaskPrint,  "TaskPrint",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskPrintHandle,APP_CPU_NUM); 
}

void loop() 
{
  digitalWrite(LED, !digitalRead(LED));
  vTaskDelay(pdMS_TO_TICKS(1000));

}

/* Função Init Harware */
void vInitHW(void)
{
    Serial.begin(9600); /* Inicializa comunicação serial com baudrate de 9600 bps */
    pinMode(LED,OUTPUT); /* configura pino do LED como saída*/

    /*INICIA DHT*/
    dht.begin();
    Serial.println("DHT22 SENSOR IDENTIFICADO");

    // /*INICIA WIFI*/
    // WiFi.begin(ssid, password);

    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(500);
    //     Serial.println("Conectando ao WiFi..");
    // }
    // Serial.println("Conectado na rede WiFi");
}

/*Função DHT*/
void vTaskDHT (void *pvParameters)
{
  (void) pvParameters;
  sensor_t sensor;
  sensors_event_t event;
  while(1)
  {
    dht.temperature().getSensor(&sensor);
    Serial.println("Temperatura:");

    dht.humidity().getSensor(&sensor);
    Serial.println("Umidade:");
      
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println("Erro ao ler a temperatura");
    }
    else {
      Serial.print("Temperatura: ");
      Serial.print(event.temperature);
      Serial.println(" *C");
    }

    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println("Erro ao ler a Umidade");
    }
    else {
      Serial.print("Umidade: ");
      Serial.print(event.relative_humidity);
      Serial.println("%");
    }
    
  }
}