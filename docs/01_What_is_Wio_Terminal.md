# Wio Terminal 有什么好玩的？



## Wio Terminal 是什么

**Wio Terminal** 是 Seeed Studio 设计的一款开发套件。它基于 SAMD51 的微控制器，运行速度为 120MHz（最高可达 200MHz），拥有 4MB 外部闪存和 192KB RAM，具有 Realtek RTL8720DN 支持的无线连接，同时支持蓝牙和 Wi-Fi 功能，并且兼容 Arduino 和 MicroPython，是物联网项目的一个不错选择。

Wio Terminal 自身配有 2.4 寸 LCD 屏幕、板载 IMU（LIS3DHTR）、麦克风、蜂鸣器、microSD 卡槽、光传感器和红外发射器（IR 940nm）。另外，它还有两个用于 Grove 生态系统的多功能 Grove 端口和兼容树莓派的 40 pin 接口，可用于支持更多附加组件。

![](https://static.getiot.tech/wio-terminal-resources-layout.png)



## 为什么要用 Wio Terminal

因为 Wio Terminal 虽然身材小巧，但拥有 ARM Cortex-M4 内核，并搭载了相当丰富的外设，包括 LCD 显示屏和一些传感器，并且支持 Arduino 和 MicroPython，这简直太棒了！

### 应用场景

下面列举一些 Wio Terminal 的应用场景：

- Python 终端设备
- 手持设备
- 物联网控制器
- 原型开发
- 用于机器学习的数据收集设备
- 复古游戏设备
- 教育
- Raspberry Pi 的从设备和附件

### 主要特性

- **高度集成的设计**
  - 与 Arduino Uno 相当的体积，集成了 MCU、LCD、Wi-Fi、蓝牙、IMU、麦克风、 蜂鸣器、microSD 卡、可配置的按钮、光传感器、五向开关、红外发射器等硬件。
- **由 Microchip ATSAMD51P19 驱动**
  - Arm® Cortex®-M4F 核心，4 MB 外部闪存，192 KB RAM；
  - 支持 SPI、I2C、I2S、ADC、DAC、PWM 和 UART 接口。
- **强大的无线连接**
  - 由 Realtek RTL8720DN 提供技术支持；
  - 双频 2.4 GHz / 5 GHz Wi-Fi（802.11 a/b/g/n）；
  - BL / BLE 5.0 蓝牙。
- **Grove 生态系统**
  - 用于探索物联网的 300 多个 Grove 模块；
  - 两个板载多功能 Grove 端口可用于数字、模拟、 I2C 和 PWM；
  - 简洁易懂的 100% 开源硬件设计；
  - 使用 LCD 屏幕和紧凑型外壳，无需费力从零搭建；
  - 用易于使用的图形元素和漂亮的可视化编辑工具创建嵌入式 GUI。
- **USB OTG 支持**
  - 可作为 USB 主机和客户端；
  - 模拟鼠标、键盘、MIDI 设备、Xbox/PS 游戏控制器和 3D 打印机等。
- **兼容40针Raspberry**
  - 可以作为从设备安装到 Raspberry Pi；
  - Raspberry Pi 的 HAT 可以与适配器电缆一起使用。
- **软件支持**
  - [Arduino](https://www.arduino.cc/en/software)
  - [ArduPy](https://wiki.seeedstudio.com/ArduPy/)
  - [MicroPython](https://micropython.org/)
  - AT 固件



### 硬件分布

![](https://static.getiot.tech/WioT-Hardware-Overview.png)



## 怎么用 Wio Terminal

Wio Terminal 支持使用 Arduino IDE 进行开发。Arduino IDE 可以在[这里](https://www.arduino.cc/en/software)下载，它支持 Windows、Linux 和 MacOS 平台，下面以 Ubuntu 为例进行演示，介绍如何搭建 Wio-Terminal 的开发环境并运行 Blink 程序，具体步骤如下。

![](https://static.getiot.tech/wio-terminal-powerup.png)



**1、安装 Arduino IDE**

安装过程可以参考 [Arduino 开发环境](https://getiot.tech/arduino/arduino-ide.html)。

**2、打开 Blink 示例**

打开 LED 闪烁示例项目，位置：*File（文件） > Examples（示例） > 01.Basics > Blink*

**3、将 Wio Terminal 添加到您的 Arduino IDE**

点击 *File（文件） > Preference（偏好设置）* ，打开“首选项”页面，将以下网址复制到“附加开发板管理器网址”（Additional Boards Manager URLs）一栏。

```bash
https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
```

如下图所示：

![](https://static.getiot.tech/Arduino-IDE-add-Wio-Terminal.png)

点击 *Tools（工具） > Board（开发板）> Boards Manager...* ，打开“开发板管理器”，在搜索栏中搜索关键字 **Wio Terminal** 后，点击并安装 **Seeed SAMD Boards** 最新版本。

![](https://static.getiot.tech/Arduino-IDE-Board-Manager-add-Seeed-SAMD.png)

**4、设置开发板和串行端口**

在 *Tools（工具）> Board（开发板）* 菜单中选择“Seeed SAMD”项，选择 **Seeed Wio Terminal** 开发板。

从 *Tools（工具）> Serial Port（端口）* 中选择 Wio Terminal 的串行设备。在 Ubuntu 系统中通常为 /dev/ttyACM0，Windows 系统则是 COM 端口。如果你不知道具体是哪个，可以先断开 Wio Terminal 并重新打开菜单，消失的条目应该是它的串口，接着重新连接电路板并选择该串行端口即可。

**5、上传程序**

现在可以点击工具栏中的 **上传（Upload）** 按钮，Arduino IDE 会先编译 Blink 程序，编译成功后烧写到 Wio-Terminal 中。如果一切顺利，状态栏中将显示“上传成功（Done uploading）”的信息。

这时候，我们可以看到 Wio Terminal 下方的蓝色 LED 开始闪烁。这样，说明 Wio-Terminal 的开发环境已经搭建成功。

![](https://static.getiot.tech/Arduino-IDE-Wio-Terminal-Blink.png)





## 资源链接

- [Wio Terminal 入门教程](https://wiki.seeedstudio.com/cn/Wio-Terminal-Getting-Started/)
- [Wio Terminal 开发教程](https://getiot.tech/category/wiot)

