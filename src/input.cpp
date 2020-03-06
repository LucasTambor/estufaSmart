#include <Arduino.h>
#include <Keypad.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "input.h"
#include "commom.h"

const byte numRows= 4;
const byte numCols= 4;
char keymap[numRows][numCols]= {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'} };


byte rowPins[numRows] = {PIN_ROW_1, PIN_ROW_2, PIN_ROW_3, PIN_ROW_4}; //Rows 0 to 3
byte colPins[numCols]= {PIN_COLUMN_1, PIN_COLUMN_2, PIN_COLUMN_3, PIN_COLUMN_4}; //Columns 0 to 3

void vTaskInput(void *pvParameters) {
  (void) pvParameters;
  char incomingChar = '0';
  Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

  while(1) {
    incomingChar = myKeypad.getKey();
    if (incomingChar != NO_KEY) {
      xQueueSend(xCommandQueue, &incomingChar, portMAX_DELAY);
      Serial.print("Incoming Char: ");
      Serial.println(incomingChar);
    }

    vTaskDelay(pdMS_TO_TICKS(300));
  }
}