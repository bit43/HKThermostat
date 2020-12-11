#include <arduino_homekit_server.h>

//==============================
// Homekit setup and loop
//==============================

// access your homekit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_temperature;
extern "C" homekit_characteristic_t target_temperature;
extern "C" homekit_characteristic_t cha_humidity;
extern "C" homekit_characteristic_t current_state;
extern "C" homekit_characteristic_t target_state;

void homekitSetup() {
    arduino_homekit_setup(&config);
}

void hk_updateHumidity(float value) {
	cha_humidity.value.float_value = value;
	homekit_characteristic_notify(&cha_humidity, cha_humidity.value);
}

void hk_updateTemperature(float value) {
	cha_temperature.value.float_value = value;
	homekit_characteristic_notify(&cha_temperature, cha_temperature.value);
}

void hk_updateState(int value) {
	current_state.value.int_value = value;
	homekit_characteristic_notify(&current_state, current_state.value);
}

