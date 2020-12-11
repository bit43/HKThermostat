#include <Arduino.h>
#include <wifi_connector.h>
#include <react.h>

void setup() {
	Serial.begin(115200);
	setupIr();
	setupDisplay();
	wifiConnect();
	homekitSetup();
	cleanDisplay();
}

void loop() {
	reactLoop();
	delay(50);
}