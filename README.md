# Sensor_STHS34PF80
 ## 简介

本软件包是为 ST STHS34PF80 传感器提供的通用传感器驱动包。通过使用此软件包，开发者可以快速的利用 RT-Thread 将此传感器驱动起来。

本篇文档主要内容如下：

- 传感器介绍
- 支持情况
- 使用说明

## 传感器介绍

STHS34PF80 是 ST 推出的小封装的红外传感器，用于存在检测，运动检测以及温度检测，带有3个中断源

## 支持情况

| 包含设备         | 运动检测 | 存在检测 | 温度检测
| ---------------- | ------ | ------ |------ |
| **通讯接口**     |        |        |        |
| IIC              | √      | √      |√      |
| SPI              |        |        |        |
| **工作模式**     |        |        |        |
| 轮询             | √      | √      |√      |
| 中断             | √      | √      |√      |
| FIFO             |       |       |        |
| **电源模式**     |        |        |        |
| 掉电             | √      | √      |√      |
| 低功耗           | √      | √      |√      |
| 普通             | √      | √      |√      |
| 高功耗           |        |        |        |
| **数据输出速率** | √      | √      |√      |
| **测量范围**     |        |        |        |
| **自检**         |        |        |        |
| **多实例**       | √      | √       |√      |

## 使用说明

### 依赖

- RT-Thread 4.0.0+
- Sensor 组件
- IIC 驱动：STHS34PF80 设备使用 IIC 进行数据通讯，需要系统 IIC 驱动框架支持；
- PIN 驱动：用于处理设备中断引脚；

### 获取软件包

使用 STHS34PF80 软件包需要在 RT-Thread 的包管理中选中它，具体路径如下：

```
RT-Thread online packages --->
    peripheral libraries and drivers --->
        sensors drivers --->
            [*] STHS34PF80: STHS34PF80 sensor driver package --->
                    Version (latest)  --->
```

**Version**：软件包版本选择

### 使用软件包

STHS34PF80 软件包初始化函数如下所示：

```
int rt_hw_sths34pf80_init(const char *name, struct rt_sensor_config *cfg);
```

该函数需要由用户调用，函数主要完成的功能有，

- 设备配置和初始化（根据传入的配置信息，配置接口设备和中断引脚）；
- 注册相应的传感器设备，完成 STHS34PF80 设备的注册；

#### 初始化示例

```
#include "sensor_st_sths34pf80.h"

int sths34pf80_port(void)
{
    uint8_t STHS34PF80_ADDR_DEFAULT = 0x5A;
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c1";
    cfg.intf.user_data = (void *)STHS34PF80_ADDR_DEFAULT;
    cfg.irq_pin.pin = RT_PIN_NONE;
    cfg.irq_pin.mode = PIN_MODE_INPUT;

    rt_hw_sths34pf80_init("sths34pf80", &cfg);
    return 0;
}
INIT_APP_EXPORT(sths34pf80_port);
```

## 注意事项

暂无

## 联系人信息

维护人:

- [Rick](https://github.com/zyk6271) 

