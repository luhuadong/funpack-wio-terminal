#include <Adafruit_AHTX0.h>
#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "seeed_line_chart.h"
#include <sfud.h>

Adafruit_AHTX0 aht;
TFT_eSPI       tft;
TFT_eSprite    spr = TFT_eSprite(&tft);  // Sprite 

typedef enum {
    SENSOR_TYPE_TEMP = 0,
    SENSOR_TYPE_HUMI = 1,
    SENSOR_TYPE_SIZE  = 2
} sensor_type;

char *titles[SENSOR_TYPE_SIZE] = {"Temperature", "Humidity"};

#define max_size 30 //maximum size of data
doubles sensorData[SENSOR_TYPE_SIZE]; //Initilising a doubles type to store data

#define SFUD_DEMO_TEST_BUFFER_SIZE                     1024
static uint8_t sfud_demo_test_buf[SFUD_DEMO_TEST_BUFFER_SIZE];

enum {
    PAGE_1 = 1,
    PAGE_2 = 2,
    PAGE_3 = 3,
    PAGE_MAX = PAGE_3
};

int currentPage = PAGE_1;
boolean pageChanged = false;

void button_handler_left() {
    pageChanged = true;
    currentPage--;
    if (currentPage < PAGE_1) {
        currentPage = PAGE_MAX;
    }
    
    Serial.print("prev page: ");
    Serial.println(currentPage);
}

void button_handler_right() {
    pageChanged = true;
    currentPage++;
    if (currentPage > PAGE_MAX) {
        currentPage = PAGE_1;
    }
    
    Serial.print("next page: ");
    Serial.println(currentPage);
}

void setup() 
{
    pinMode(WIO_KEY_A,    INPUT_PULLUP);
    pinMode(WIO_KEY_B,    INPUT_PULLUP);
    pinMode(WIO_KEY_C,    INPUT_PULLUP);
    pinMode(WIO_5S_UP,    INPUT_PULLUP);
    pinMode(WIO_5S_DOWN,  INPUT_PULLUP);
    pinMode(WIO_5S_LEFT,  INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(WIO_5S_LEFT),  button_handler_left,  FALLING);
    attachInterrupt(digitalPinToInterrupt(WIO_5S_RIGHT), button_handler_right, FALLING);
    
    Serial.begin(115200);
    Serial.println(">> Funpack Smart Air <<");

    tft.init();
    tft.setRotation(3);
    tft.fillScreen(tft.color565(24,15,60));
    tft.fillScreen(TFT_BLUE);
    tft.setFreeFont(FMB12);
    tft.setCursor((320 - tft.textWidth("Funpack Smart Air"))/2, 120);
    tft.print("Funpack Smart Air");

    spr.createSprite(TFT_HEIGHT, TFT_WIDTH);

    while(!(sfud_init() == SFUD_SUCCESS));
#ifdef SFUD_USING_QSPI
    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
#endif
    sfud_demo(0, sizeof(sfud_demo_test_buf), sfud_demo_test_buf);

    if (! aht.begin()) {
        Serial.println("Could not find AHT? Check wiring");
        while (1) delay(10);
    }
    Serial.println("AHT10 or AHT20 found");

    drawSensorPage();
}

void updateSensorData(const float temp, const float humi)
{
    if (sensorData[SENSOR_TYPE_TEMP].size() == max_size) {
        sensorData[SENSOR_TYPE_TEMP].pop();//this is used to remove the first read variable
    }
    sensorData[SENSOR_TYPE_TEMP].push(temp); //read variables and store in data

    if (sensorData[SENSOR_TYPE_HUMI].size() == max_size) {
        sensorData[SENSOR_TYPE_HUMI].pop();//this is used to remove the first read variable
    }
    sensorData[SENSOR_TYPE_HUMI].push(humi); //read variables and store in data
}

void loop()
{
    sensors_event_t humi, temp;
    aht.getEvent(&humi, &temp);// populate temp and humidity objects with fresh data
    //Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
    //Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

#if 0
    // This is used to print out on Serial Plotter, check Serial Plotter!
    Serial.print(temp.temperature);
    Serial.print(",");
    Serial.println(humi.relative_humidity);
#endif

    updateSensorData(temp.temperature, humi.relative_humidity);

    switch (currentPage) {
      case PAGE_1:
      {
        if (pageChanged) {
          drawSensorPage();
          pageChanged = false;
        }
        drawTempValue(temp.temperature);
        drawHumiValue(humi.relative_humidity);
      } break;
      case PAGE_2:
      {
        drawLineChart(SENSOR_TYPE_TEMP, TFT_RED);
      } break;
      case PAGE_3:
      {
        drawLineChart(SENSOR_TYPE_HUMI, TFT_BLUE);
      } break;
      default: break;
    }

    delay(500);
}

void drawSensorPage()
{
    // -----------------LCD---------------------

    tft.fillScreen(tft.color565(24,15,60));
    tft.setFreeFont(FF17);
    tft.setTextColor(tft.color565(224,225,232));
    //tft.drawString("Smart Air Dashboard", 80, 10);
    tft.drawString("Funpack Smart Air", 85, 10);
 
    tft.fillRoundRect(10,  45, 145, 180, 5, tft.color565(40,40,86));
    tft.fillRoundRect(165, 45, 145, 180, 5, tft.color565(40,40,86));

    tft.setFreeFont(FM9);
    tft.drawString("Temperature", 25, 60);
    tft.drawString("degrees C",   35, 200);
    tft.drawString("Humidity",   195, 60);
    tft.drawString("% rH",       220, 200);
}

void drawTempValue(const float temp) {
   tft.setFreeFont(FMB24);
   tft.setTextColor(TFT_RED, tft.color565(40,40,86));
   tft.drawString(String(temp, 1), 30, 120);
}

void drawHumiValue(const float humi) {
   tft.setFreeFont(FMB24);
   tft.setTextColor(TFT_GREEN, tft.color565(40,40,86));
   tft.drawString(String(humi, 1), 180, 120);
}

void drawLineChart(const sensor_type type, const int color) {
    spr.fillSprite(TFT_WHITE);

    //Settings for the line graph title
    auto header =  text(0, 0)
                .value(titles[type])
                .align(center)
                .valign(vcenter)
                .width(tft.width())
                .thickness(2);

    header.height(header.font_height() * 2);
    header.draw(); //Header height is the twice the height of the font

    //Settings for the line graph
    auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
         content
                .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                .width(tft.width() - content.x() * 2) //actual width of the line chart
                .based_on(0.0) //Starting point of y-axis, must be a float
                .show_circle(false) //drawing a cirle at each point, default is on.
                .value(sensorData[type]) //passing through the data to line graph
                .color(color) //Setting the color for the line
                .draw();

    spr.pushSprite(0, 0);
}

/**
 * SFUD demo for the first flash device test.
 *
 * @param addr flash start address
 * @param size test flash size
 * @param size test flash data buffer
 */
static void sfud_demo(uint32_t addr, size_t size, uint8_t *data) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_flash *flash = sfud_get_device_table() + 0;
    size_t i;
    /* prepare write data */
    for (i = 0; i < size; i++) {
        data[i] = i;
    }
    /* erase test */
    result = sfud_erase(flash, addr, size);
    if (result == SFUD_SUCCESS) {
        Serial.println("Erase the flash data finish");
    } else {
        Serial.println("Erase flash data failed");
        return;
    }
    /* write test */
    result = sfud_write(flash, addr, size, data);
    if (result == SFUD_SUCCESS) {
        Serial.println("Write the flash data finish");
    } else {
        Serial.println("Write the flash data failed");
        return;
    }
    /* read test */
    size_t BaseTime = micros();
    result = sfud_read(flash, addr, size, data);
    size_t CostTime = micros() - BaseTime;
    if (result == SFUD_SUCCESS) {
        Serial.println("Read the flash data success.");
        Serial.println("Offset (h) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");
        for (i = 0; i < size; i++) {
            if (i % 16 == 0) {
                Serial.print("0x");
                Serial.print(addr + i,HEX);
                Serial.print("\t");
            }
            Serial.print(data[i],HEX);
            Serial.print("\t");
            if (((i + 1) % 16 == 0) || i == size - 1) {
                Serial.println("");
            }
        }
        Serial.println(" ");
    } else {
        Serial.println("Read the flash data failed.");
    }
    /* data check */
    for (i = 0; i < size; i++) {
        if (data[i] != i % 256) {
            Serial.println("Read and check write data has an error.");
            break;
        }
    }
    if (i == size) {
        Serial.println("The flash test is success.\r\n");
        Serial.print("read costTime: ");
        Serial.print(CostTime);
        Serial.println(" us");
    }
}
