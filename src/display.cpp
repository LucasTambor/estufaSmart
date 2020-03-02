
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

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
      local_command = '0';
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
  uint32_t local_rssi = 0;

  display.setCursor(0, 4);

  xSemaphoreTake( xHorarioMutex, portMAX_DELAY );
  display.print(horario); // Adiciona o texto à lista de escrita do display
  xSemaphoreGive( xHorarioMutex );

  xSemaphoreTake( xWifiRssiMutex, portMAX_DELAY );
  local_rssi = rssi;
  xSemaphoreGive( xWifiRssiMutex );

  setWifiIcon(local_rssi);

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
      return DISPLAY_HOME;

      break;
    case 'c':
    case 'C':
      return DISPLAY_HOME;

      break;
    case 'd':
    case 'D':
      return DISPLAY_HOME;

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

  display.setCursor(0, 4);

  display.print("Configuracao de Luz");
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
      return DISPLAY_LIGHT_MENU;
      break;
    case 'a':
    case 'A':
      return DISPLAY_LIGHT_MENU;
      break;
    case 'b':
    case 'B':
      return DISPLAY_HOME;

      break;
    case 'c':
    case 'C':
      return DISPLAY_HOME;

      break;
    case 'd':
    case 'D':
      return DISPLAY_HOME;

      break;
    case '#':
      return DISPLAY_HOME;

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
  (void) command;
}

uint8_t displayLightOFFConfState(char command) {
  (void) command;
}

uint8_t displaySetPointMenuState(char command) {
  (void) command;
}

uint8_t displaySetPointTemperatureConfState(char command) {
  (void) command;
}

uint8_t displaySetPointHumidityConfState(char command) {
  (void) command;
}

uint8_t displayMotorMenuState(char command) {
  (void) command;
}

uint8_t displayMotorSpeedMenuState(char command) {
  (void) command;
}

uint8_t displayOperationModeState(char command) {
  (void) command;
}

//***************************************************************************************************************************

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