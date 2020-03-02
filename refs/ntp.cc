#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "icons.h"

#define PC_BLACK 0x0000
#define PC_BLUE 0x001F
#define PC_RED 0xF800
#define PC_GREEN 0x07E0
#define PC_CYAN 0x07FF
#define PC_MAGENTA 0xF81F
#define PC_YELLOW 0xFFE0
#define PC_WHITE 0xFFFF

// Configurações do WiFi
const char* ssid     = "badDaysSpaceship2"; // Nome da rede WiFi
const char* password = "+ps3=dw71102"; // Senha da rede WiFi

// Configurações do Servidor NTP
const char* servidorNTP = "a.st1.ntp.br"; // Servidor NTP para pesquisar a hora

const int fusoHorario = -10800; // Fuso horário em segundos (-03h = -10800 seg)
const int taxaDeAtualizacao = 1800000; // Taxa de atualização do servidor NTP em milisegundos

WiFiUDP ntpUDP; // Declaração do Protocolo UDP
NTPClient timeClient(ntpUDP, servidorNTP, fusoHorario, 60000);


// Configuração do Display OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setWifi(int32_t rssi);

void setup()
{
  // Declarar Serial para realizar debug do código
  Serial.begin(115200);
  delay(10);


  // Conectar ao WiFi
  WiFi.begin(ssid, password);


  // Iniciar display e configurar interface
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);


  // Aguardando conexão do WiFi
  while (WiFi.status() != WL_CONNECTED)
  {
      display.clearDisplay();
      display.print("...");
      display.display();

      Serial.print(".");
      delay(500);
  }

  Serial.println("");
  Serial.print("WiFi conectado. Endereço IP: ");
  Serial.println(WiFi.localIP());


  // Iniciar cliente de aquisição do tempo
  timeClient.begin();
}

void loop()
{

  timeClient.update();
  Serial.println(timeClient.getFormattedTime());

  String horario = timeClient.getFormattedTime();

  display.clearDisplay(); // Limpa o conteúdo do display
  display.setCursor(0, 4);
  display.print(horario); // Adiciona o texto à lista de escrita do display
  setWifi(WiFi.RSSI());
  display.drawLine(0, 18, SCREEN_WIDTH, 18, WHITE); // Adiciona uma linha à lista de escrita do display
  display.display(); // Escreve as informações da lista de escrita no display
  delay(800);
}


void setWifi(int32_t rssi) {
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
