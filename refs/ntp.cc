#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include <Wire.h>
#include <SSD1306Wire.h>


// Configurações do WiFi
const char* ssid     = "nome-da-rede-wifi"; // Nome da rede WiFi
const char* password = "senha-da-rede-wifi"; // Senha da rede WiFi


// Configurações do Servidor NTP
const char* servidorNTP = "a.st1.ntp.br"; // Servidor NTP para pesquisar a hora

const int fusoHorario = -10800; // Fuso horário em segundos (-03h = -10800 seg)
const int taxaDeAtualizacao = 1800000; // Taxa de atualização do servidor NTP em milisegundos

WiFiUDP ntpUDP; // Declaração do Protocolo UDP
NTPClient timeClient(ntpUDP, servidorNTP, fusoHorario, 60000);


// Configuração do Display OLED
SSD1306Wire display(0x3C, 5, 4);


void setup()
{
  // Declarar Serial para realizar debug do código
  Serial.begin(115200);
  delay(10);


  // Conectar ao WiFi
  WiFi.begin(ssid, password);


  // Iniciar display e configurar interface
  display.init();
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER);


  // Aguardando conexão do WiFi
  while (WiFi.status() != WL_CONNECTED)
  {
      display.clear();
      display.drawString(63, 12, "...");
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

  display.clear(); // Limpa o conteúdo do display
  display.drawString(63, 19, horario); // Adiciona o texto à lista de escrita do display
  display.drawLine(10, 52, 117, 52); // Adiciona uma linha à lista de escrita do display
  display.display(); // Escreve as informações da lista de escrita no display

  delay(800);
}