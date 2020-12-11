#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library
#include <Wire.h>

#define TFT_DC D1  // TFT DC  pin is connected to NodeMCU pin D1 (GPIO5)
#define TFT_RST D0 // TFT RST pin is connected to NodeMCU pin D2 (GPIO4)
#define TFT_CS D8  // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int currentTempBarValue = 0;

void drowGrid() {
    uint16_t gridColor = 0x5CB9;

    tft.drawFastVLine(0, 0, 240, gridColor); 

    tft.drawFastHLine(0, 0, 195, gridColor); 

    tft.drawFastVLine(195, 0, 240, gridColor);

    tft.drawFastHLine(0, 239, 195, gridColor); 

    tft.drawFastHLine(0, 60, 195, gridColor); 

    tft.drawFastVLine(97, 0, 60, gridColor);
}

// from 0 to 38
void drowTargetTempBar(int count) {

    int to = 239 - ((count * 6) + 11);

    uint16_t lineColor = ST77XX_RED;

    for (int i = 239; i >= 0; i--) {

        if (i >= to) {
           tft.drawFastHLine(200, i, 55, lineColor); 
        } else {
            tft.drawFastHLine(200, i, 55, ST77XX_BLACK); 
        }
        
    }   
}

void setupDisplay()
{
    tft.init(240, 240, SPI_MODE2); // Init ST7789 display 240x240 pixel
    tft.fillScreen(ST77XX_BLACK);

    tft.setCursor(50, 150);
    tft.setTextSize(3);

    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.println("Starting");
}

void cleanDisplay()
{
    tft.fillScreen(ST77XX_BLACK);
    drowGrid();
}

void disp_updateCurrentTemperature(float value) {
    tft.setTextWrap(true);
    tft.setCursor(10, 25);
    tft.setTextSize(2);

    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.printf("%.1f C", value);
}

void disp_updateCurrentHumidity(float value) {
    tft.setTextWrap(true);
    tft.setCursor(115, 25);
    tft.setTextSize(2);

    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.printf("%.1f %%", value);
}

void disp_updateTarget(float value)
{

    tft.setTextWrap(true);
    tft.setCursor(40, 140);
    tft.setTextSize(5);

    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.printf("%.1f", value);
    drowTargetTempBar((int) value);

}

void disp_updateState(String value)
{
    tft.setTextWrap(true);
    tft.setCursor(20, 80);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);

    tft.print(value);

}

