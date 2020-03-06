#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "commom.h"
// #include "dht.h"
#include "DHT11.h"

float temperature_value = 0;
uint8_t humidity_value = 0;

static gpio_num_t dht_gpio;
static int64_t last_read_time = -2000000;
dht_t last_read;

void vTaskDHT(void *pvParameters) {
  (void) pvParameters;
  DHT11_init((gpio_num_t)4);

  bool init_task = 0;
  while(!init_task) {
    xSemaphoreTake( xWifiReadyMutex, pdMS_TO_TICKS(200) );
    init_task = wifi_ready;
    xSemaphoreGive( xWifiReadyMutex );

    vTaskDelay(pdMS_TO_TICKS(500));
  }

  while(1)
  {
      dht_t dht_value = DHT11_read();
      if(dht_value.status == DHT11_OK)
      {
        temperature_value = dht_value.temperature;
        humidity_value = dht_value.humidity;
      }else{
          Serial.print("DHT ERROR: "); Serial.println(dht_value.status);
      }

    vTaskDelay(pdMS_TO_TICKS(READ_DHT_PERIOD_MS));
  }
}



//*******************************************************************************************

void DHT11_init(gpio_num_t gpio_num) {
    /* Wait 1 seconds to make the device pass its initial unstable status */
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    dht_gpio = gpio_num;
}

//*******************************************************************************************

static int _waitOrTimeout(uint16_t microSeconds, int level) {
    int micros_ticks = 0;
    while(gpio_get_level(dht_gpio) == level) {
        if(micros_ticks++ > microSeconds)
            return DHT11_TIMEOUT_ERROR;
        ets_delay_us(1);
    }
    return micros_ticks;
}

//*******************************************************************************************

static int _checkCRC(uint8_t data[]) {
    if(data[4] == (data[0] + data[1] + data[2] + data[3]))
        return DHT11_OK;
    else
        return DHT11_CRC_ERROR;
}

//*******************************************************************************************

static void _sendStartSignal() {
    gpio_set_direction(dht_gpio, GPIO_MODE_OUTPUT);
    gpio_set_level(dht_gpio, 0);
    ets_delay_us(20 * 1000);
    gpio_set_level(dht_gpio, 1);
    ets_delay_us(40);
    gpio_set_direction(dht_gpio, GPIO_MODE_INPUT);
}

//*******************************************************************************************

static int _checkResponse() {
    /* Wait for next step ~80us*/
    if(_waitOrTimeout(80, 0) == DHT11_TIMEOUT_ERROR)
        return DHT11_TIMEOUT_ERROR;

    /* Wait for next step ~80us*/
    if(_waitOrTimeout(80, 1) == DHT11_TIMEOUT_ERROR)
        return DHT11_TIMEOUT_ERROR;

    return DHT11_OK;
}

//*******************************************************************************************

dht_t _timeoutError() {
    dht_t timeoutError = {DHT11_TIMEOUT_ERROR, -1, -1};
    return timeoutError;
}

//*******************************************************************************************

dht_t _crcError() {
    dht_t crcError = {DHT11_CRC_ERROR, -1, -1};
    return crcError;
}

//*******************************************************************************************

dht_t _outOfBoundsError() {
    dht_t outOfBoundsError = {DHT_OUT_OF_BOUNDS_ERROR, -1, -1};
    return outOfBoundsError;
}

//*******************************************************************************************

dht_t DHT11_read() {
    /* Tried to sense too son since last read (dht11 needs ~2 seconds to make a new read) */
    if(esp_timer_get_time() - 2000000 < last_read_time) {
        return last_read;
    }

    last_read_time = esp_timer_get_time();

    uint8_t data[5] = {0,0,0,0,0};

    _sendStartSignal();

    if(_checkResponse() == DHT11_TIMEOUT_ERROR)
        return last_read = _timeoutError();

    /* Read response */
    for(int i = 0; i < 40; i++) {
        /* Initial data */
        if(_waitOrTimeout(50, 0) == DHT11_TIMEOUT_ERROR)
            return last_read = _timeoutError();

        if(_waitOrTimeout(70, 1) > 28) {
            /* Bit received was a 1 */
            data[i/8] |= (1 << (7-(i%8)));
        }
    }

    if(_checkCRC(data) != DHT11_CRC_ERROR) {
        if(data[0] > 100)
        {
            return _outOfBoundsError();
        }else{
            last_read.status = DHT11_OK;
            last_read.temperature = data[2];
            last_read.humidity = data[0];
            return last_read;
        }
    } else {
        return last_read = _crcError();
    }
}