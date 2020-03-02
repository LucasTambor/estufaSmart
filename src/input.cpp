#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "icons.h"
#include "commom.h"

void vTaskInput(void *pvParameters) {
  (void) pvParameters;
  char incomingChar = '0';
  while(1) {
    if(Serial.available()){
      incomingChar = Serial.read();

      Serial.print("Incoming Char: ");
      Serial.println(incomingChar);

      xQueueSend(xCommandQueue, &incomingChar, portMAX_DELAY);
    }

    vTaskDelay(pdMS_TO_TICKS(300));
  }
}