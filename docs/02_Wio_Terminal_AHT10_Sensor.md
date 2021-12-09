# Wio Terminal 读取 AHT10 传感器



![](https://static.getiot.tech/Wio-Terminal-Smart-Air-001.jpg)



## 读取数据

```cpp
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  delay(500);
}
```





## 显示数据

```cpp
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

    tft.init();
    tft.setRotation(3);
    tft.fillScreen(tft.color565(24,15,60));

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

    tft.setFreeFont(FF17);
    tft.setTextColor(tft.color565(224,225,232));
    tft.drawString("Funpack Smart Air", 85, 10);
 
    tft.fillRoundRect(10,  45, 145, 180, 5, tft.color565(40,40,86));
    tft.fillRoundRect(165, 45, 145, 180, 5, tft.color565(40,40,86));
 
    tft.setFreeFont(FM9);
    tft.drawString("Temperature", 25, 60);
    tft.drawString("degrees C",   35, 200);
    tft.drawString("Humidity",   195, 60);
    tft.drawString("% rH",       220, 200);
 
    tft.setFreeFont(FMB24);
    tft.setTextColor(TFT_RED);
    tft.drawString(String(temp, 1), 30, 120);
    tft.setTextColor(TFT_GREEN);
    tft.drawString(String(humi, 1), 180, 120);
}
```



