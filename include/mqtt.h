#ifndef _MQTT_H_
#define _MQTT_H_

#include <Arduino.h>


void MqttReconect();
void SubCallback(char* topic, byte* payload, unsigned int length);
void subscribeToTopics();

#endif //_MQTT_H_