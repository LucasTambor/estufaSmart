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
 TaskHandle_t xTaskDHTHandle,xTaskPrintHandle,xTaskPWMHandle;

/* Defines */
#define LED 2
#define DHTPIN            4 
#define DHTTYPE   DHT22
#define MOTOR 16
#define UMIDIFICADOR 19

// GPIO CONECTA MORTOR
const int ledPin = 16;  // GPIO16

// PROGRAMAÇÃO PWM
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

/* Protótipo das Tasks*/
 void vTaskDHT(void *pvParameters);
 void vTaskPWM(void *pvParameters);
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
    1,
    &xTaskDHTHandle,
    APP_CPU_NUM);   
  /* Cria a vTaskPWM */
  xTaskCreatePinnedToCore(vTaskPWM,
  "TaskPrint", 
  configMINIMAL_STACK_SIZE + 1024, 
  NULL, 
  2, 
  &xTaskPWMHandle,
  APP_CPU_NUM); 
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
    
    // CONFIGURAÇAO PWM MOTOR
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(ledPin, ledChannel);

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

/*FUNÇÃO PWM*/
void vTaskPWM(void *pvParameters)
{
  (void) pvParameters;
      // AUMENTANDO A VELOCIDADE
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {   
    ledcWrite(ledChannel, dutyCycle);
    Serial.println("ACELERANDO");
    delay(15);
  }

  // DIMINUINDO A VELOCIDADE
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    ledcWrite(ledChannel, dutyCycle);   
    Serial.println("REDUZINDO");
    delay(15);
  }
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