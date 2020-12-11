#include <display.h>
#include <homekit.h>
#include <sensors.h>
#include <ir.h>

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

float realHumidity;
float realTemperature;
float targetTemperature;
uint8_t state;

// need for slowdown sensors read
int tact = 0;

void checkHumidity()
{

    float tmpH = getHumidity();

    if (isnan(tmpH))
    {
        LOG_D("ERROR! Can't read humidity");
        return;
    }

    if (tmpH != realHumidity)
    {
        LOG_D("INFO! Humidity updated. Current - %.1f", tmpH);

        // replace stored for next check
        realHumidity = tmpH;

        // update display value
        disp_updateCurrentHumidity(realHumidity);

        // update homekit value
        hk_updateHumidity(realHumidity);

    }
}

void checkTemperature()
{

    float tmpT = getTemperature();

    if (isnan(tmpT))
    {
        LOG_D("ERROR! Can't read temperature");
        return;
    }

    if (tmpT != realTemperature)
    {
        LOG_D("INFO! Temperature updated. Current - %.1f", tmpT);
        realTemperature = tmpT;
        disp_updateCurrentTemperature(realTemperature);
        hk_updateTemperature(realTemperature);
    }
}

void checkTargetTemperature()
{
    float tmpTargetT = target_temperature.value.float_value;

    if (isnan(tmpTargetT))
    {
        LOG_D("ERROR! Can't target temperature");
        return;
    }

    if (tmpTargetT != targetTemperature)
    {
        LOG_D("INFO! Target temperature updated. Current - %.1f", tmpTargetT);
        targetTemperature = tmpTargetT;
        disp_updateTarget(targetTemperature);
        setTemperature(targetTemperature);
    }
}

void checkCurrentState()
{
    uint8_t tmpState = target_state.value.int_value;

    if (isnan(tmpState))
    {
        LOG_D("ERROR! Can't check current state");
        return;
    }

    if (tmpState != state)
    {
        String stateStr;

        switch (tmpState)
        {
        case 0:
            stateStr = "OFF";
        case 1:
            stateStr = "HEAT";
            break;
        case 2:
            stateStr = "COOL";
            break;
        case 3:
            stateStr = "AUTO";
            break;
        default:
            stateStr = "ERROR";
            break;
        }

        LOG_D("INFO! State updated. Current - %i", tmpState);
        state = tmpState;
        disp_updateState(stateStr);
        hk_updateState(state);
    }
}

void updateSensors() {

    if (tact >= 20) {
        checkHumidity();
        checkTemperature();
        tact = 0;
    }
    
    tact++;
}

void reactLoop()
{
    // internal homekit loop (update internal state and comunicate with clients)
    arduino_homekit_loop();
    checkTargetTemperature();
    checkCurrentState();
    updateSensors();
    
}