#include <iostream>
#include <string>
/*bibliotecas para MQTT*/
#include <WiFi.h>
#include <PubSubClient.h>
#include "commom.h"
#include "mqtt.h"

#define _DEBUG_MQTT_

/* instacias para WIFI e client*/
WiFiClient espClient;
PubSubClient client(espClient);

/* configuraçãoes da REDE e broker MQTT*/
const char* mqttServer = "mqtt.eclipse.org";
const int mqttPort = 1883;
const char* mqttUser = "lucastambor";
const char* mqttPassword = "lucastambortbm";

//**********************************************************************************************************

bool mqttState = 0;
bool operation_state = 0;
bool light_state = 0;

//**********************************************************************************************************
//Topicos
//get
const char* mqttTopicSubOpState ="param/get/state";
const char* mqttTopicSubLightState ="state/get/light";

//set
const char* mqttTopicPubOpState ="param/set/state";
const char* mqttTopicPubLightState ="state/set/light";

/*Implementação da Task MQTT */
void vTaskMqtt(void *pvParameters){
  (void) pvParameters;
  char buffer[32];
  // int valor_recebido = 0;
  bool init_task = 0;
  while(!init_task) {
    xSemaphoreTake( xWifiReadyMutex, pdMS_TO_TICKS(200) );
    init_task = wifi_ready;
    xSemaphoreGive( xWifiReadyMutex );

    vTaskDelay(pdMS_TO_TICKS(500));
  }

  client.setServer(mqttServer, mqttPort);

  // Callback para topicos subscribe
  client.setCallback(SubCallback);

  while(1) {
    if(!client.connected()){
      mqttState = 0;
      MqttReconect();
    }
    mqttState = 1;
    //Op Mode
    xSemaphoreTake( xOpStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", operation_state);
    xSemaphoreGive( xOpStateMutex );
    client.publish(mqttTopicPubOpState, buffer);

    //Light State
    xSemaphoreTake( xLightStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", light_state);
    xSemaphoreGive( xLightStateMutex );
    client.publish(mqttTopicPubLightState, buffer);

    client.loop();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


//função pra reconectar ao servido MQTT
void MqttReconect() {
  //Enquanto estiver desconectado
  while (!client.connected()) {

    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      subscribeToTopics();
    } else {
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }
}

void SubCallback(char* topic, byte* payload, unsigned int length) {
  //armazena msg recebida em uma sring
  payload[length] = '\0';
  String strMSG = String((char*)payload);

  // char logBuff[100];
#ifdef _DEBUG_MQTT_
  Serial.print("Mensagem chegou do tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem:");
  Serial.print(strMSG);
  Serial.println();
  Serial.println("-----------------------");
#endif

  if(!strcmp(topic, mqttTopicSubOpState)) { // Topico Operation State
    xSemaphoreTake( xOpStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    operation_state = atoi(strMSG.c_str());
    xSemaphoreGive( xOpStateMutex );
  }

  if(!strcmp(topic, mqttTopicSubLightState)) { // Topico Operation State
    xSemaphoreTake( xLightStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    light_state = atoi(strMSG.c_str());
    xSemaphoreGive( xLightStateMutex );
  }

}

void subscribeToTopics() {
  client.subscribe(mqttTopicSubOpState);
  client.subscribe(mqttTopicSubLightState);

}