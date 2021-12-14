# Wio Terminal 从网络获取天气数据



本文主要介绍如何使用 Wio Terminal 的 WiFi 网络获取天气数据。



## WiFi 配置

Wio Terminal 配备的无线网卡是 Realtek RTL8720，在开始本次学习之前，请确保你已经阅读 [Wio Terminal 网卡固件更新](https://getiot.tech/wiot/wio-terminal-network-firmware.html)，并完成固件更新和 Arduino 依赖库的安装。

我们知道，WiFi 有两种工作模式：AP 模式和 STA 模式。

- AP（Access Point）也就是无线接入点，是一个无线网络的创建者，是网络的中心节点。一般家庭或办公室使用的无线路由器就一个 AP。
- STA（Station）也就是站点，每一个连接到无线网络中的终端（如笔记本电脑、PDA 及其它可以联网的用户设备）都可称为一个站点。

在本示例中，Wio Terminal 工作在 STA 模式。下面代码使用 **rpcWiFi** 库将 Wio Terminal 连接到指定的 WiFi 网络。

提示：需要将 `ssid` 和 `password` 修改为你的 WiFi 网络。

```cpp
#include "rpcWiFi.h"

const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPassword";

void setup() {
    Serial.begin(115200);
    while(!Serial); // Wait for Serial to be ready
 
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
 
    Serial.println("Connecting to WiFi..");
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
        WiFi.begin(ssid, password);
    }
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println (WiFi.localIP()); // prints out the device's IP address
    }
 
void loop() {
 
}
```



## 天气 API

有很多提供天气信息的 Web API，可以参考《[一些好用的天气 API](https://getiot.tech/article/the-best-weather-api.html)》，本文使用高德地图 API 获取实时天气及天气预测。GET 请求的 URL 如下：

**实时天气**（当天）

```bash
https://restapi.amap.com/v3/weather/weatherInfo?city=441802&key=yourkey
```

**天气预测**（未来三天）

```bash
https://restapi.amap.com/v3/weather/weatherInfo?city=441802&key=yourkey&extensions=all
```

参数说明：

- `city` 是城市编码，比如 441802 代表广州；
- `key` 是应用对应的代码，需要在平台申请（提示：将 `yourkey` 替换为你申请的 Key 代码）；
- `extensions` 表示获取类型，缺省值是 `base`，表示获取实况天气，`all` 表示获取预报天气；
- `output` 表示返回格式，可选 JSON 或 XML，默认返回 JSON 格式数据。

以实时天气 API 为例，返回的 JSON 数据如下：

```json
{
    "status":"1",
    "count":"1",
    "info":"OK",
    "infocode":"10000",
    "lives":[
        {"province":"广东",
         "city":"广州市",
         "adcode":"440100",
         "weather":"晴",
         "temperature":"17",
         "winddirection":"北",
         "windpower":"≤3",
         "humidity":"64",
         "reporttime":"2021-12-12 19:00:44"
        }
    ]
}
```



## HTTP 客户端

下面代码使用 HTTPClient 创建 HTTP 连接，通过高德地图 API 请求实况天气信息，并输出到串口。

提示：将下面代码中的 `ssid` 和 `password` 替换成你的 WiFi 网络；将 `URL` 中的 `cityCode` 替换成需要查询的城市，将 `yourKey` 替换成你的 Key。

```cpp
#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPassword";

const char* URL = "https://restapi.amap.com/v3/weather/weatherInfo?city=cityCode&key=yourKey";

WiFiClientSecure client;

void setup()
{
    Serial.begin(115200);
    
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) { //Check for the connection
        delay(500);
        Serial.println("Connecting WiFi...");
    }
    Serial.print("Connected to the WiFi network with IP: ");
    Serial.println(WiFi.localIP());
    //client.setCACert(test_root_ca);
}

void loop() 
{
    if(&client) {   
        getWeather();
    }
    delay(30000);
}

void getWeather()
{
    // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is
    HTTPClient https;
    
    Serial.print("[HTTPS] begin...\n");
    
    if (https.begin(client, URL))
    {
        Serial.print("[HTTPS] GET...\n");
        
        int httpCode = https.GET();
        
        if (httpCode > 0)
        {
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
            
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {
                String payload = https.getString();
                Serial.println(payload);
            }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
        
        https.end();
        
    } else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
    // End extra scoping block
}
```

编译上传到 Wio Terminal，打开 Arduino IDE 的串口监视器，输出内容如下：

```json
Connected to the WiFi network with IP: 192.168.3.189
[HTTPS] begin... weather lives
[HTTPS] GET...
[HTTPS] GET... code: 200
{"status":"1","count":"1","info":"OK","infocode":"10000","lives":[{"province":"广东","city":"清城区","adcode":"441802","weather":"晴","temperature":"19","winddirection":"东北","windpower":"≤3","humidity":"54","reporttime":"2021-12-12 12:30:59"}]}
```

