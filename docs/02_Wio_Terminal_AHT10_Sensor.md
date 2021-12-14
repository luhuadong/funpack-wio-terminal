# Wio Terminal 读取 AHT10 传感器



本文介绍如何通过 Wio Terminal 读取 AHT10 传感器的温湿度数据。



## AHT10 传感器

AHT10 是一款高精度、完全校准、贴片封装的温湿度传感器，采用 I2C 信号输出，可测量温度范围 -40~+85℃，分辨率达 0.01℃。

![](https://static.getiot.tech/Sensor-ATH10-2.jpg)



## 读取数据

这里使用 Adafruit AHTX0 库读取 AHT10 传感器数据，返回浮点类型的温度和湿度值。

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

显示数据部分依赖 TFT LCD 库，库在安装 *Seeed SAMD Boards* 库时已经包含了，大家可以参考 [Wio Terminal 开发环境](https://getiot.tech/wiot/wio-terminal-development-environment.html)。另外，我们还使用了 `Free_Fonts.h` 库提供的一些免费字体，可以点击[这里](https://files.seeedstudio.com/wiki/Wio-Terminal/res/Free_Fonts.h)下载，并将它放在 Arduino 工程中。

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



## 运行效果

![](https://static.getiot.tech/Wio-Terminal-Smart-Air-001.jpg)

