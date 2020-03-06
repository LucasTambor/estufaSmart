#ifndef DHT11_H_
#define DHT11_H_

#include "driver/gpio.h"

#define READ_DHT_PERIOD_MS 2000

enum dht11_status {
    DHT11_OK = 0,
    DHT11_CRC_ERROR,
    DHT11_TIMEOUT_ERROR,
    DHT_OUT_OF_BOUNDS_ERROR,
};

typedef struct{
    int8_t status;
    double temperature;
    int8_t humidity;
}dht_t;

void DHT11_init(gpio_num_t);

dht_t DHT11_read();

#endif //DHT11_H