# Funpack Wio Terminal
—— 硬禾学堂 Funpack 12 期「Wio Terminal 开发板」说明文档

![](https://www.eetree.cn/storage/page/digikey-funpack/image/12/banner.png)

## 任务

- **任务 1**：利用扩展接口，自由选择连接三到五个传感器，并将采集的数据显示在 LCD 屏幕上，并解释数据的含义。
- **任务 2**：制作一个自动联网的天气预报仪，在设计界面显示温湿度、天气情况、空气质量以及未来三天内的天气变化。
- **任务 3**：使用麦克风采集使用者说话口型并识别，同时在屏幕上画出对应的表情。



## 自我介绍

大家好，我是 Rudy，业余时间喜欢折腾一些开源软件和硬件，正在努力成为一名真正创客，利用开源和科技的力量做出能促进社会进步的产品。



## 实现功能

本期任务：

- 开机自动联网获取实况天气和预报天气；
- 在主界面同时显示室外和室内的温湿度；
- 按上方左键可手动更新天气信息；
- 可通过五向开关的 Left 和 Right 翻页查看未来几天的天气预测。

![](https://static.getiot.tech/Funpack12_WioT_WeatherBox_Pro.png)

针对这次活动和实现的功能，我一共整理了六篇文章：

1. [Wio Terminal 有什么好玩的？](https://luhuadong.blog.csdn.net/article/details/121924371)
2. [Wio Terminal 读取 AHT10 传感器](https://luhuadong.blog.csdn.net/article/details/121924554)
3. [Wio Terminal 将数据存储到 Flash](https://luhuadong.blog.csdn.net/article/details/121924656)
4. [Wio Terminal 从网络获取天气数据](https://luhuadong.blog.csdn.net/article/details/121924844)
5. [Wio Terminal 天气小助手项目](https://luhuadong.blog.csdn.net/article/details/121924915)
5. [Wio Terminal LCD 中文显示](https://luhuadong.blog.csdn.net/article/details/121939994)

视频和代码链接如下：

- 视频介绍：<https://www.bilibili.com/video/BV1Cq4y127wy/> 
- 代码仓库：<https://github.com/luhuadong/funpack-wio-terminal>

Wio Terminal 天气小助手的固件代码位于 firmware/WeatherBox 目录，可通过 Arduino IDE 打开，编译并上传到 Wio Terminal。当然，为了顺利编译，你通常还需要安装一些依赖库（看文档说明）。



## 心得体会

这是 Funpack 第12期，也是第一届 Funpack 活动的最后一期，真心感谢得捷电子和硬禾学堂为我们带来这么棒的活动！不仅能一边玩一边学，还能锻炼视频剪辑和表达能力，让离开校园多年的我们重新感受到了校园学习的氛围。

本期的 Wio Terminal 开发套件也很给力，它支持 Arduino 和 MicroPython 编程，同时提供了 Grove 和 RPI 接口，可以无缝对接 Arduino、树莓派和 SeeedStudio Grove 的生态系统，大大提高了 Wio Terminal 的可玩性。愈发让我觉得，Wio Terminal 绝对不只是一块开发板那么简单，它能做很多事情，无论是 DIY 项目、青少年教育、边缘人工智能等等，都让人对它充满了想象。

由于时间关系，我只在该项目中融合了任务一和任务二，设计了「天气小助手」项目，通过传感器获取室内温湿度，通过网络获取实况天气和预报天气。关于 TinyML 部分仍在学习，我想虽然第一届 Funpack 活动结束了，但我们学习的脚步并不会因此停止，希望未来能做出更多好玩有趣且实用的项目。

最后，再次感谢得捷电子和硬禾学堂，感谢 Funpack 第1期至第12期的各位小伙伴！

2021年12月14日，Rudy



![](https://static.getiot.tech/Funpack12_Wio_Terminal_Cover.jpeg)



## 资料

- [Wio Terminal 入门教程](https://wiki.seeedstudio.com/cn/Wio-Terminal-Getting-Started/)
- [Wio-Terminal 开发教程](https://getiot.tech/category/wiot)
