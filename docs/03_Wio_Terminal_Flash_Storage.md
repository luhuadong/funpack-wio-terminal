# Wio Terminal 将数据存储到 Flash



Wio Terminal 内置了一片 4MB 大小的 Flash 闪存，我们可以通过 QSPI 访问它。下面就来介绍如何通过 Wio Terminal 读写内置的 Flash 存储器。



## 安装依赖库

首先需要为 Wio Terminal 安装 `Seeed_Arduino_FS` 文件系统库和 `Seeed_Arduino_SFUD` 库。

1、在 `Seeed_Arduino_FS` 的 [GitHub 仓库](https://github.com/Seeed-Studio/Seeed_Arduino_FS) 下载 zip 包。

2、在 `Seeed_Arduino_SFUD` 的 [GitHub 仓库](https://github.com/Seeed-Studio/Seeed_Arduino_SFUD) 下载 zip 包。

3、然后打开 Arduino IDE，点击 *项目 > 加载库 > 添加 .ZIP 库…*，添加这两个库。



## 示例代码

下面将演示如何对这块 Flash 进行读写擦（Read/Erase/Write）：

```cpp
#include <sfud.h>
 
#define SFUD_DEMO_TEST_BUFFER_SIZE                     1024
static uint8_t sfud_demo_test_buf[SFUD_DEMO_TEST_BUFFER_SIZE];
static void sfud_demo(uint32_t addr, size_t size, uint8_t *data);
 
#define SERIAL Serial
 
void setup()
{
    SERIAL.begin(115200);
    while(!SERIAL) {};
    while(!(sfud_init() == SFUD_SUCCESS));
    #ifdef SFUD_USING_QSPI
    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    #endif
    sfud_demo(0, sizeof(sfud_demo_test_buf), sfud_demo_test_buf);
}
 
void loop()
{
 
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
        SERIAL.println("Erase the flash data finish");
    } else {
        SERIAL.println("Erase flash data failed");
        return;
    }
    /* write test */
    result = sfud_write(flash, addr, size, data);
    if (result == SFUD_SUCCESS) {
        SERIAL.println("Write the flash data finish");
    } else {
        SERIAL.println("Write the flash data failed");
        return;
    }
    /* read test */
    size_t BaseTime = micros();
    result = sfud_read(flash, addr, size, data);
    size_t CostTime = micros() - BaseTime;
    if (result == SFUD_SUCCESS) {
        SERIAL.println("Read the flash data success.");
        SERIAL.println("Offset (h) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");
        for (i = 0; i < size; i++) {
            if (i % 16 == 0) {
                SERIAL.print("0x");
                SERIAL.print(addr + i,HEX);
                SERIAL.print("\t");
            }
            SERIAL.print(data[i],HEX);
            SERIAL.print("\t");
            if (((i + 1) % 16 == 0) || i == size - 1) {
                SERIAL.println("");
            }
        }
        SERIAL.println(" ");
    } else {
        SERIAL.println("Read the flash data failed.");
    }
    /* data check */
    for (i = 0; i < size; i++) {
        if (data[i] != i % 256) {
            SERIAL.println("Read and check write data has an error.");
            break;
        }
    }
    if (i == size) {
        SERIAL.println("The flash test is success.\r\n");
        SERIAL.print("read costTime: ");
        SERIAL.print(CostTime);
        SERIAL.println(" us");
    }
}
```



## 运行效果

编译并上传程序到 Wio Terminal，打开串口监视器可以看到如下打印：

![img](https://static.getiot.tech/wio-terminal-sfud-flash.png)

