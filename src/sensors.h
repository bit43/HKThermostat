#include "DHT.h"   

#define DHT11PIN 10

DHT dht11(DHT11PIN, DHT11); //DHT11 sensor init

boolean isBegin = false;

void setupSensors() {
    dht11.begin();
    isBegin = true;
}

float getHumidity() {

    if (!isBegin) {
        setupSensors();
    }

    return dht11.readHumidity();
}

float getTemperature() {

    if (!isBegin) {
        setupSensors();
    }

    return dht11.readTemperature();
}

