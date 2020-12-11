#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h> 

#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_

#include <ESP8266WiFi.h>

void wifiConnect() {

	WiFiManager wifiManager;

	wifiManager.autoConnect("HKThermostat");

	WiFi.persistent(false);
	WiFi.setAutoReconnect(true);

	printf("WiFi connected! IP: %s", WiFi.localIP().toString().c_str());

}

#endif /* WIFI_INFO_H_ */
