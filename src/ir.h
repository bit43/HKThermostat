#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Neoclima.h>

const uint16_t kIrLed = 2;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRNeoclimaAc ac(kIrLed);

void printState() {
  // Display the settings.
  Serial.println("A/C remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
  Serial.println();
}

void setupIr()
{   
    Serial.println("INFO! Starting IR");
    ac.begin();
    ac.calibrate();
    Serial.println("INFO! IR Started");
    printState();
}

void turnOn() {
    Serial.println("INFO! IR ON");
    ac.setPower(true);
    ac.on();
    ac.send();
}

void turnOff() {
    Serial.println("INFO! IR OFF");
    ac.off();
    ac.send();
}

void setTemperature(int value) {

    Serial.printf("INFO! IR Set tmp %i", value);
        ac.setPower(true);

    ac.on();
    ac.setTemp(value, true);
    ac.send();
}

void heat() {
    Serial.println("INFO! IR HEAT");
    ac.setMode(kNeoclimaHeat);
    ac.send();
}

void cool() {
    Serial.println("INFO! IR COOL");
    ac.setMode(kNeoclimaCool);
    ac.send();
}


