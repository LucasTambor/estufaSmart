
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "icons.h"
#include "commom.h"
#include "display.h"
#include "eepromEstufa.h"

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String schedule_light_ON = "";
String schedule_light_OFF = "";

void vTaskDisplay(void *pvParameters) {
  (void) pvParameters;
  bool init_task = 0;
  char local_command = '0';

  // Iniciar display e configurar interface
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.print("Initializing WIFI...");
  display.display();

  while(!init_task) {
    xSemaphoreTake( xWifiReadyMutex, pdMS_TO_TICKS(200) );
    init_task = wifi_ready;
    xSemaphoreGive( xWifiReadyMutex );

    vTaskDelay(pdMS_TO_TICKS(500));
  }

  while(1) {
    if(xQueueReceive(xCommandQueue, &local_command, pdMS_TO_TICKS(50)) != pdTRUE){
      local_command = ' ';
    }

    display.clearDisplay(); // Limpa o conteúdo do display
    display.drawLine(0, 18, SCREEN_WIDTH, 18, WHITE); // Adiciona uma linha à lista de escrita do display
    DisplayControl(local_command);
    display.display(); // Escreve as informações da lista de escrita no display
    vTaskDelay(pdMS_TO_TICKS(100));

  }
}

//***************************************************************************************************************************

void DisplayControl(char command) {
  static uint8_t displayState = DISPLAY_HOME;

  switch(displayState) {
    case DISPLAY_HOME:
        displayState = displayHomeState(command);
      break;
    case DISPLAY_LIGHT_MENU:
        displayState = displaylighMenuState(command);
      break;
    case DISPLAY_LIGHT_ON_CONF:
        displayState = displayLightOnConfState(command);
      break;
    case DISPLAY_LIGHT_OFF_CONF:
        displayState = displayLightOFFConfState(command);
      break;
    case DISPLAY_SET_POINT_MENU:
        displayState = displaySetPointMenuState(command);
      break;
    case DISPLAY_SET_POINT_TEMPERATURE_CONF:
        displayState = displaySetPointTemperatureConfState(command);
      break;
    case DISPLAY_SET_POINT_HUMIDITY_CONF:
        displayState = displaySetPointHumidityConfState(command);
      break;
    case DISPLAY_MOTOR_MENU:
        displayState = displayMotorMenuState(command);
      break;
    case DISPLAY_MOTOR_SPEED_CONF:
        displayState = displayMotorSpeedMenuState(command);
      break;
    case DISPLAY_OPERATION_MODE_CONF:
        displayState = displayOperationModeState(command);
      break;
    default:
      break;
  }
}

//***************************************************************************************************************************

uint8_t displayHomeState(char command){
  char buffer[32] = {0};
  uint32_t local_rssi = 0;
  bool local_op_state = 0;
  bool local_light_state = 0;
  bool local_motor_state = 0;
  bool local_hum_state = 0;

  display.setCursor(0, 4);
  // Time
  xSemaphoreTake( xHorarioMutex, portMAX_DELAY );
  display.print(horario);
  xSemaphoreGive( xHorarioMutex );

  //RSSI
  xSemaphoreTake( xWifiRssiMutex, portMAX_DELAY );
  local_rssi = rssi;
  xSemaphoreGive( xWifiRssiMutex );

  //Light
  xSemaphoreTake( xLightStateMutex, portMAX_DELAY );
  local_light_state = light_state;
  xSemaphoreGive( xLightStateMutex );

  //Mqtt
  setWifiIcon(local_rssi);
  setMqttIcon(mqttState);
  setLighIcon(local_light_state);

  //Op Mode
  xSemaphoreTake( xOpStateMutex, portMAX_DELAY );
  local_op_state = operation_mode;
  xSemaphoreGive( xOpStateMutex );
  sprintf(buffer, "%s", local_op_state ? "manual" : "auto");
  display.setCursor(50, 57);
  display.print(buffer);

  //Motor State
  xSemaphoreTake( xMotorStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  local_motor_state = motor_state;
  xSemaphoreGive( xMotorStateMutex );
  setMotorIcon(local_motor_state);

  //Humidifier State
  xSemaphoreTake( xHumidifierMutex, pdMS_TO_TICKS(portMAX_DELAY) );
  local_hum_state = humidifier_state;
  xSemaphoreGive( xHumidifierMutex );
  setHumidifierIcon(local_hum_state);


  //Temperature
  display.setCursor(0, 57);
  sprintf(buffer, "%2.2fC", temperature_value);
  display.print(buffer);

  //Humidity
  display.setCursor(SCREEN_WIDTH - 20, 57);
  sprintf(buffer, "%d%%", humidity_value);
  display.print(buffer);

  switch(command) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return DISPLAY_HOME;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*':
      return DISPLAY_HOME;

      break;
    default:
      return DISPLAY_HOME;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displaylighMenuState(char command){
  //title
  display.setCursor(6, 4);
  display.print("Schedule Light Conf");

  //body
  display.setCursor(6, 30);
  display.println("1. Schedule turn ON");
  display.setCursor(6, 50);
  display.println("2. Schedule turn OFF");

  switch(command) {
    case '1':
      return DISPLAY_LIGHT_ON_CONF;
      break;

    case '2':
      return DISPLAY_LIGHT_OFF_CONF;
      break;

    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      if(operation_mode == MANUAL_MODE) {
        xSemaphoreTake( xLightStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
        light_state = !light_state;
        saveToEeprom(LIGHT_STATE_ADDR, light_state);
        xSemaphoreGive( xLightStateMutex );
      }
      return DISPLAY_LIGHT_MENU;
      break;
    case '*':
      return DISPLAY_HOME;

      break;
    default:
      return DISPLAY_LIGHT_MENU;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displayLightOnConfState(char command) {
  char buffer[32] = {0};
  static uint8_t char_count = 0;
  static String temp = "";
  display.setTextSize(1);

  //title
  display.setCursor(6, 4);
  display.print("Schedule light ON");

  //body
  display.setCursor(6, 30);

  sprintf(buffer, "Actual Value: %s", schedule_light_ON.c_str() );
  display.println(buffer);

  display.setCursor(6, 40);
  display.print("New Value: ");
  display.print(temp);

  switch(command) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
      if(char_count < 4) {
        char_count++;
        temp += command;
        if(char_count == 2) {
          temp += ':';
        }
      }
      return DISPLAY_LIGHT_ON_CONF;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':

      return DISPLAY_HOME;

      break;
    case '*': //Save and return
      xSemaphoreTake( xLightScheduleMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      schedule_light_ON = temp;
      char_count = 0;
      temp = "";
      saveStringToEeprom(LIGHT_SCHEDULE_ON_ADDR, schedule_light_ON);
      xSemaphoreGive( xLightScheduleMutex );
      return DISPLAY_LIGHT_MENU;

      break;
    default:
      return DISPLAY_LIGHT_ON_CONF;

      break;
  }

}

//***************************************************************************************************************************

uint8_t displayLightOFFConfState(char command) {
  char buffer[32] = {0};
  static uint8_t char_count = 0;
  static String temp = "";
  display.setTextSize(1);

  //title
  display.setCursor(6, 4);
  display.print("Schedule light OFF");

  //body
  display.setCursor(6, 30);

  sprintf(buffer, "Actual Value: %s", schedule_light_OFF.c_str() );
  display.println(buffer);

  display.setCursor(6, 40);
  display.print("New Value: ");
  display.print(temp);

  switch(command) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
      if(char_count < 4) {
        char_count++;
        temp += command;
        if(char_count == 2) {
          temp += ':';
        }
      }
      return DISPLAY_LIGHT_OFF_CONF;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*': //Save and return
      xSemaphoreTake( xLightScheduleMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      schedule_light_OFF = temp;
      Serial.print("New Schedule: ");Serial.println(schedule_light_OFF);
      char_count = 0;
      temp = "";
      saveStringToEeprom(LIGHT_SCHEDULE_OFF_ADDR, schedule_light_OFF);
      xSemaphoreGive( xLightScheduleMutex );
      return DISPLAY_LIGHT_MENU;

      break;
    default:
      return DISPLAY_LIGHT_OFF_CONF;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displaySetPointMenuState(char command) {
  //title
  display.setCursor(3, 4);
  display.print("Light Set Point Conf");

  //body
  display.setCursor(6, 30);
  display.println("1. Temp set point");
  display.setCursor(6, 50);
  display.println("2. hum set point");

  switch(command) {
    case '1':
      return DISPLAY_SET_POINT_TEMPERATURE_CONF;
      break;

    case '2':
      return DISPLAY_SET_POINT_HUMIDITY_CONF;
      break;

    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return DISPLAY_SET_POINT_MENU;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*':
      return DISPLAY_HOME;

      break;
    default:
      return DISPLAY_SET_POINT_MENU;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displaySetPointTemperatureConfState(char command) {
  char buffer[32] = {0};
  static uint8_t char_count = 0;
  static String temp = "";
  display.setTextSize(1);

  //title
  display.setCursor(30, 4);
  display.print("Temperature");

  //body
  display.setCursor(6, 30);

  sprintf(buffer, "Actual Value: %d C", temperature_set_point );
  display.println(buffer);

  display.setCursor(6, 40);
  display.print("New Value: ");
  display.print(temp);

  switch(command) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
      if(char_count < 2) {
        char_count++;
        temp += command;
      }
      return DISPLAY_SET_POINT_TEMPERATURE_CONF;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*': //Save and return
      xSemaphoreTake( xTemperatureSetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      temperature_set_point = atoi(temp.c_str());
      char_count = 0;
      temp = "";
      saveToEeprom(TEMP_SET_POINT_ADDR, temperature_set_point);
      xSemaphoreGive( xTemperatureSetPointMutex );
      return DISPLAY_SET_POINT_MENU;

      break;
    default:
      return DISPLAY_SET_POINT_TEMPERATURE_CONF;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displaySetPointHumidityConfState(char command) {
  char buffer[32] = {0};
  static uint8_t char_count = 0;
  static String temp = "";
  display.setTextSize(1);

  //title
  display.setCursor(40, 4);
  display.print("Humidity");

  //body
  display.setCursor(6, 30);

  sprintf(buffer, "Actual Value: %d %%", humidity_set_point );
  display.println(buffer);

  display.setCursor(6, 40);
  display.print("New Value: ");
  display.print(temp);

  switch(command) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
      if(char_count < 2) {
        char_count++;
        temp += command;
      }
      return DISPLAY_SET_POINT_HUMIDITY_CONF;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*': //Save and return
      xSemaphoreTake( xHumiditySetPointMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      humidity_set_point = atoi(temp.c_str());
      char_count = 0;
      temp = "";
      saveToEeprom(HUMIDITY_SET_POINT_ADDR, humidity_set_point);
      xSemaphoreGive( xHumiditySetPointMutex );

      return DISPLAY_SET_POINT_MENU;

      break;
    default:
      return DISPLAY_SET_POINT_HUMIDITY_CONF;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displayMotorMenuState(char command) {
  //title
  display.setCursor(6, 4);
  display.print("Motor Configuration");

  //body
  display.setCursor(6, 30);
  display.println("1. Motor Speed");

  switch(command) {
    case '1':
      return DISPLAY_MOTOR_SPEED_CONF;
      break;

    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return DISPLAY_MOTOR_MENU;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*':
      return DISPLAY_HOME;

      break;
    default:
      return DISPLAY_MOTOR_MENU;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displayMotorSpeedMenuState(char command) {
  char buffer[32] = {0};
  static uint8_t char_count = 0;
  static String temp = "";
  display.setTextSize(1);

  //title
  display.setCursor(30, 4);
  display.print("Motor Speed");

  //body
  display.setCursor(6, 30);

  sprintf(buffer, "Actual Value: %d %%", motor_speed );
  display.println(buffer);

  display.setCursor(6, 40);
  display.print("New Value: ");
  display.print(temp);

  switch(command) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
      if(char_count < 2) {
        char_count++;
        temp += command;
      }
      return DISPLAY_MOTOR_SPEED_CONF;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*': //Save and return
      xSemaphoreTake( xMotorSpeedMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      motor_speed = atoi(temp.c_str());
      char_count = 0;
      temp = "";
      saveToEeprom(MOTOR_SPEED_ADDR, motor_speed);
      xSemaphoreGive( xMotorSpeedMutex );
      return DISPLAY_MOTOR_MENU;

      break;
    default:
      return DISPLAY_MOTOR_SPEED_CONF;

      break;
  }
}

//***************************************************************************************************************************

uint8_t displayOperationModeState(char command) {
  char buffer[32] = {0};
  static bool original_op_mode = operation_mode;
  static bool temp_op_mode = original_op_mode;
  display.setTextSize(1);

  //title
  display.setCursor(25, 4);
  display.print("Operation Mode");

  //body
  display.setCursor(6, 30);
  sprintf(buffer, "Actual Value: %s", original_op_mode ? "manual" : "auto");
  display.println(buffer);

  display.setCursor(6, 40);
  sprintf(buffer, "New Value: %s", temp_op_mode ? "manual" : "auto");
  display.print(buffer);

  switch(command) {
    case '1':
      temp_op_mode = !temp_op_mode;
      return DISPLAY_OPERATION_MODE_CONF;
      break;
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':

      return DISPLAY_OPERATION_MODE_CONF;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_SET_POINT_MENU;

      break;
    case 'c':
    case 'C':
      return DISPLAY_MOTOR_MENU;

      break;
    case 'd':
    case 'D':
      return DISPLAY_OPERATION_MODE_CONF;

      break;
    case '#':
      return DISPLAY_HOME;

      break;
    case '*': //Save and return
      xSemaphoreTake( xOpStateMutex, pdMS_TO_TICKS(portMAX_DELAY) );
      operation_mode = temp_op_mode;
      xSemaphoreGive( xOpStateMutex );
      saveToEeprom(OPERATION_MODE_ADDR, operation_mode);
      return DISPLAY_HOME;

      break;
    default:
      return DISPLAY_OPERATION_MODE_CONF;

      break;
  }
}

//***************************************************************************************************************************
//Set ICON Functions

void setWifiIcon(int32_t rssi) {
  if(rssi >= -60) { // High Quality
    display.drawBitmap(SCREEN_WIDTH-16, 0, wifi1_icon16x16, 16, 16, 1);
  }
  else if(rssi < -60 && rssi >= -80) { // Medium Quality
    display.drawBitmap(SCREEN_WIDTH-16, 0, wifi2_icon16x16, 16, 16, 1);
  }
  else if(rssi < -80 ) { // Medium Quality
    display.drawBitmap(SCREEN_WIDTH-16, 0, wifi3_icon16x16, 16, 16, 1);
  }
}

void setMqttIcon(bool state) {
  if(state){
    display.drawBitmap(SCREEN_WIDTH-36, 0, heart_icon16x16, 16, 16, 1);
  }
}

void setLighIcon(bool state) {
  if(state) {
    display.drawBitmap(10, 30, bulb_on_icon16x16, 16, 16, 1);
  }else {
    display.drawBitmap(10, 30, bulb_off_icon16x16, 16, 16, 1);
  }
}

void setMotorIcon(bool state) {
  if(state) {
    display.drawBitmap(60, 30, motor_on_icon16x16, 16, 16, 1);
  }else {
    display.drawBitmap(60, 30, motor_off_icon16x16, 16, 16, 1);
  }
}

void setHumidifierIcon(bool state) {
  if(state) {
    display.drawBitmap(106, 30, humidity_on_icon16x16, 16, 16, 1);
  }else {
    display.drawBitmap(106, 30, humidity_off_icon16x16, 16, 16, 1);
  }}
