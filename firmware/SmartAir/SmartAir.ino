#include <Adafruit_AHTX0.h>
#include "Free_Fonts.h"
#include "TFT_eSPI.h"

Adafruit_AHTX0 aht;
TFT_eSPI       tft;

boolean pageChanged = true;

void setup() 
{
    Serial.begin(115200);
    Serial.println(">> Funpack Smart Air <<");

    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLUE);
    tft.setFreeFont(FMB12);
    tft.setCursor((320 - tft.textWidth("Funpack Smart Air"))/2, 120);
    tft.print("Funpack Smart Air");

    if (! aht.begin()) {
        Serial.println("Could not find AHT? Check wiring");
        while (1) delay(10);
    }
    Serial.println("AHT10 or AHT20 found");
}

void loop()
{
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
    Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

    getSensorData(temp.temperature, humidity.relative_humidity);

    delay(2000);
}

void getSensorData(const float temp, const float humi)
{
    // -----------------LCD---------------------

    //if (pageChanged) {
    tft.fillScreen(tft.color565(24,15,60));
    tft.setFreeFont(FF17);
    tft.setTextColor(tft.color565(224,225,232));
    tft.drawString("Smart Air Dashboard", 80, 10);
 
    tft.fillRoundRect(10,  45, 145, 180, 5, tft.color565(40,40,86));
    tft.fillRoundRect(165, 45, 145, 180, 5, tft.color565(40,40,86));
 
    tft.setFreeFont(FM9);
    tft.drawString("Temperature", 25, 60);
    tft.drawString("degrees C",   35, 200);
    tft.drawString("Humidity",   195, 60);
    tft.drawString("% rH",       220, 200);

    //pageChanged = false;
    //}
 
    tft.setFreeFont(FMB24);
    tft.setTextColor(TFT_RED);
    tft.drawString(String(temp, 1), 30, 120);
    tft.setTextColor(TFT_GREEN);
    tft.drawString(String(humi, 1), 180, 120);
}
