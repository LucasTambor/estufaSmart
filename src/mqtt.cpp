#include <iostream>
#include <string>
/*bibliotecas para MQTT*/
#include <WiFi.h>
#include <PubSubClient.h>
#include "commom.h"
#include "mqtt.h"
#include "eepromEstufa.h"

// #define _DEBUG_MQTT_

/* instacias para WIFI e client*/
WiFiClient espClient;
PubSubClient client(espClient);

/* configuraçãoes da REDE e broker MQTT*/
const char* mqttServer = "postman.cloudmqtt.com";
const int mqttPort = 17936;
const char* mqttUser = "mggphudi";
const char* mqttPassword = "wauG8UCgVkct";
// const char* mqttServer = "mqtt.eclipse.org";
// const int mqttPort = 1883;
// const char* mqttUser = "lucastambor";
// const char* mqttPassword = "lucastambortbm";

//**********************************************************************************************************

bool mqttState = 0;
bool operation_mode = 0;
bool light_state = 0;
bool motor_state = 0;
bool humidifier_state = 0;

uint8_t temperature_set_point = 0;
uint8_t humidity_set_point = 0;
uint8_t motor_speed = 0;

//**********************************************************************************************************
//Topicos
//get
const char* mqttTopicSubLightState ="state/get/light";
const char* mqttTopicSubMotorState ="state/get/motor";
const char* mqttTopicSubHumState ="state/get/hum";
const char* mqttTopicSubOpState ="param/get/state";
const char* mqttTopicSubLightOnParam ="param/get/light_on";
const char* mqttTopicSubLightOffParam ="param/get/light_off";
const char* mqttTopicSubTempSetParam ="param/get/temp_set";
const char* mqttTopicSubHumSetParam ="param/get/hum_set";
const char* mqttTopicSubMotorSpeedParam ="param/get/motor_speed";

//set
const char* mqttTopicPubLightState ="state/set/light";
const char* mqttTopicPubMotorState ="state/set/motor";
const char* mqttTopicPubHumState ="state/set/hum";
const char* mqttTopicPubTemperatureState ="state/set/temperature";
const char* mqttTopicPubHumidityState ="state/set/humidity";
const char* mqttTopicPubOpState ="param/set/state";
const char* mqttTopicPubLightOnParam ="param/set/light_on";
const char* mqttTopicPubLightOffParam ="param/set/light_off";
const char* mqttTopicPubTempSetParam ="param/set/temp_set";
const char* mqttTopicPubHumSetParam ="param/set/hum_set";
const char* mqttTopicPubMotorSpeedParam ="param/set/motor_speed";

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
    sprintf(buffer, "%d", operation_mode);
    xSemaphoreGive( xOpStateMutex );
    client.publish(mqttTopicPubOpState, buffer);

    //Light State
    xSemaphoreTake( xLightStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", light_state);
    xSemaphoreGive( xLightStateMutex );
    client.publish(mqttTopicPubLightState, buffer);

    //Motor State
    xSemaphoreTake( xMotorStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", motor_state);
    xSemaphoreGive( xMotorStateMutex );
    client.publish(mqttTopicPubMotorState, buffer);

    //Humidifier State
    xSemaphoreTake( xHumidifierMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", humidifier_state);
    xSemaphoreGive( xHumidifierMutex );
    client.publish(mqttTopicPubHumState, buffer);

    //Light On/Off Param
    xSemaphoreTake( xLightScheduleMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    client.publish(mqttTopicPubLightOnParam, schedule_light_ON.c_str());
    client.publish(mqttTopicPubLightOffParam, schedule_light_OFF.c_str());
    xSemaphoreGive( xLightScheduleMutex );

    //Temperature Set Point
    xSemaphoreTake( xTemperatureSetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", temperature_set_point);
    xSemaphoreGive( xTemperatureSetPointMutex );
    client.publish(mqttTopicPubTempSetParam, buffer);

    //Humidity Set Point
    xSemaphoreTake( xHumiditySetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", humidity_set_point);
    xSemaphoreGive( xHumiditySetPointMutex );
    client.publish(mqttTopicPubHumSetParam, buffer);

    //Motor Speed Set Point
    xSemaphoreTake( xMotorSpeedMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    sprintf(buffer, "%d", motor_speed);
    xSemaphoreGive( xMotorSpeedMutex );
    client.publish(mqttTopicPubMotorSpeedParam, buffer);

    //Temperature Value
    sprintf(buffer, "%2.2f", temperature_value);
    client.publish(mqttTopicPubTemperatureState, buffer);
    //Humidity Value
    sprintf(buffer, "%d", humidity_value);
    client.publish(mqttTopicPubHumidityState, buffer);

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
    operation_mode = atoi(strMSG.c_str());
    saveToEeprom(OPERATION_MODE_ADDR, operation_mode);
    xSemaphoreGive( xOpStateMutex );
  }
  if(!strcmp(topic, mqttTopicSubLightOnParam)) { // Topico light on Param
    xSemaphoreTake( xLightScheduleMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    schedule_light_ON = strMSG;
    saveStringToEeprom(LIGHT_SCHEDULE_ON_ADDR, schedule_light_ON);
    xSemaphoreGive( xLightScheduleMutex );
  }
  if(!strcmp(topic, mqttTopicSubLightOffParam)) { // Topico light off Param
    xSemaphoreTake( xLightScheduleMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    schedule_light_OFF = strMSG;
    saveStringToEeprom(LIGHT_SCHEDULE_OFF_ADDR, schedule_light_OFF);
    xSemaphoreGive( xLightScheduleMutex );
  }
  if(!strcmp(topic, mqttTopicSubTempSetParam)) { // Topico set temperature set point
    xSemaphoreTake( xTemperatureSetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    temperature_set_point = atoi(strMSG.c_str());
    saveToEeprom(TEMP_SET_POINT_ADDR, temperature_set_point);
    xSemaphoreGive( xTemperatureSetPointMutex );
  }

  if(!strcmp(topic, mqttTopicSubHumSetParam)) { // Topico set humidity set point
    xSemaphoreTake( xHumiditySetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    humidity_set_point = atoi(strMSG.c_str());
    saveToEeprom(HUMIDITY_SET_POINT_ADDR, humidity_set_point);
    xSemaphoreGive( xHumiditySetPointMutex );
  }

  if(!strcmp(topic, mqttTopicSubMotorSpeedParam)) { // Topico Motor Speed Param
    xSemaphoreTake( xMotorSpeedMutex, pdMS_TO_TICKS(portMAX_DELAY) );
    motor_speed = atoi(strMSG.c_str());
    saveToEeprom(MOTOR_SPEED_ADDR, motor_speed);
    xSemaphoreGive( xMotorSpeedMutex );
  }

  if(operation_mode) {
    if(!strcmp(topic, mqttTopicSubLightState)) { // Topico Light State
      xSemaphoreTake( xLightStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      light_state = atoi(strMSG.c_str());
      saveToEeprom(LIGHT_STATE_ADDR, light_state);
      xSemaphoreGive( xLightStateMutex );
    }

    if(!strcmp(topic, mqttTopicSubMotorState)) { // Topico Motor State
      xSemaphoreTake( xMotorStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      motor_state = atoi(strMSG.c_str());
      saveToEeprom(MOTOR_STATE_ADDR, motor_state);
      xSemaphoreGive( xMotorStateMutex );
    }

    if(!strcmp(topic, mqttTopicSubHumState)) { // Topico Humidifier State
      xSemaphoreTake( xHumidifierMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      humidifier_state = atoi(strMSG.c_str());
      saveToEeprom(HUMIDIFIER_STATE_ADDR, humidifier_state);
      xSemaphoreGive( xHumidifierMutex );
    }
  }

}

void subscribeToTopics() {
  client.subscribe(mqttTopicSubOpState);
  client.subscribe(mqttTopicSubLightState);
  client.subscribe(mqttTopicSubLightOnParam);
  client.subscribe(mqttTopicSubLightOffParam);
  client.subscribe(mqttTopicSubTempSetParam);
  client.subscribe(mqttTopicSubHumSetParam);
  client.subscribe(mqttTopicSubMotorSpeedParam);
  client.subscribe(mqttTopicSubMotorState);
  client.subscribe(mqttTopicSubHumState);
}
