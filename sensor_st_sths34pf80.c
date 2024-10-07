/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     Rick       the first version
 */
#include "sensor_st_sths34pf80.h"

#define DBG_TAG "sensor.st.sths34pf80"
#define DBG_LVL DBG_LOG


static STHS34PF80_Object_t sths34pf80;
static struct rt_i2c_bus_device *i2c_bus_dev;

static int32_t i2c_init(void)
{
    return 0;
}

static int32_t sths34pf80_get_tick(void)
{
    return rt_tick_get();
}

static int rt_i2c_write_reg(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t len)
{
    rt_uint8_t tmp = reg;
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = addr;             /* Slave address */
    msgs[0].flags = RT_I2C_WR;        /* Write flag */
    msgs[0].buf   = &tmp;             /* Slave register address */
    msgs[0].len   = 1;                /* Number of bytes sent */

    msgs[1].addr  = addr;             /* Slave address */
    msgs[1].flags = RT_I2C_WR | RT_I2C_NO_START;        /* Read flag */
    msgs[1].buf   = data;             /* Read data pointer */
    msgs[1].len   = len;              /* Number of bytes read */

    if (rt_i2c_transfer(i2c_bus_dev, msgs, 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int rt_i2c_read_reg(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t len)
{
    rt_uint8_t tmp = reg;
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = addr;             /* Slave address */
    msgs[0].flags = RT_I2C_WR;        /* Write flag */
    msgs[0].buf   = &tmp;             /* Slave register address */
    msgs[0].len   = 1;                /* Number of bytes sent */

    msgs[1].addr  = addr;             /* Slave address */
    msgs[1].flags = RT_I2C_RD;        /* Read flag */
    msgs[1].buf   = data;             /* Read data pointer */
    msgs[1].len   = len;              /* Number of bytes read */

    if (rt_i2c_transfer(i2c_bus_dev, msgs, 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
static rt_err_t _sths34pf80_init(struct rt_sensor_intf *intf)
{
    STHS34PF80_IO_t io_ctx;
    rt_uint8_t        id;

    i2c_bus_dev = (struct rt_i2c_bus_device *)rt_device_find(intf->dev_name);
    if (i2c_bus_dev == RT_NULL)
    {
        return -RT_ERROR;
    }

    /* Configure the baroelero driver */
    io_ctx.BusType     = STHS34PF80_I2C_BUS; /* I2C */
    io_ctx.Address     = (rt_uint32_t)(intf->user_data) & 0xff;
    io_ctx.Init        = i2c_init;
    io_ctx.DeInit      = i2c_init;
    io_ctx.ReadReg     = rt_i2c_read_reg;
    io_ctx.WriteReg    = rt_i2c_write_reg;
    io_ctx.GetTick     = sths34pf80_get_tick;

    sths34pf80.Config.LPF_Motion = 0x04;
    sths34pf80.Config.LPF_Presence = 0x04;
    sths34pf80.Config.LPF_Temperature = 0x02;
    sths34pf80.Config.AVG_TMOS = 0x02;
    sths34pf80.Config.ODR = 0x07;
    sths34pf80.Config.THS_Presence = 5000;
    sths34pf80.Config.THS_Motion = 2300;
    sths34pf80.Config.THS_Temp_Shock = 2000;

    if (STHS34PF80_RegisterBusIO(&sths34pf80, &io_ctx) != STHS34PF80_OK)
    {
        return -RT_ERROR;
    }
    else if (STHS34PF80_ReadID(&sths34pf80, &id) != STHS34PF80_OK)
    {
        rt_kprintf("read id failed\n");
        return -RT_ERROR;
    }
    if (STHS34PF80_Init(&sths34pf80) != STHS34PF80_OK)
    {
        rt_kprintf("sths34pf80 init failed\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}
static rt_err_t _sths34pf80_set_odr(rt_sensor_t sensor, rt_uint16_t odr)
{
    sths34pf80_ctrl1_odr_set(&sths34pf80.Ctx, odr);

    return RT_EOK;
}
static rt_size_t _sths34pf80_polling_get_data(rt_sensor_t sensor, struct rt_sensor_data *data)
{
    uint16_t val;
    switch(sensor->info.type)
    {
    case RT_SENSOR_CLASS_PROXIMITY:
        STHS34PF80_ReadPresence(&sths34pf80, &val);
        data->type = RT_SENSOR_CLASS_PROXIMITY;
        data->data.proximity = val;
        data->timestamp = rt_sensor_get_ts();
        break;
    case RT_SENSOR_CLASS_TEMP:
        STHS34PF80_ReadTemperature(&sths34pf80, &val);
        data->type = RT_SENSOR_CLASS_TEMP;
        data->data.temp = (int)(val*0.1);
        data->timestamp = rt_sensor_get_ts();
        break;
    case RT_SENSOR_CLASS_FORCE:
        STHS34PF80_ReadMotion(&sths34pf80, &val);
        data->type = RT_SENSOR_CLASS_FORCE;
        data->data.proximity = val;
        data->timestamp = rt_sensor_get_ts();
        break;
    default:
        break;
    }
    return 1;
}
static rt_err_t _sths34pf80_set_mode(rt_sensor_t sensor, rt_uint8_t mode)
{
    switch(sensor->info.type)
    {
    case RT_SENSOR_CLASS_PROXIMITY:
        if(mode == RT_SENSOR_MODE_INT)
        {
            STHS34PF80_ControlINT(&sths34pf80,2,1);
        }
        break;
    case RT_SENSOR_CLASS_TEMP:
        if(mode == RT_SENSOR_MODE_INT)
        {
            STHS34PF80_ControlINT(&sths34pf80,0,1);
        }
        break;
    case RT_SENSOR_CLASS_FORCE:
        if(mode == RT_SENSOR_MODE_INT)
        {
            STHS34PF80_ControlINT(&sths34pf80,1,1);
        }
        break;
    default:
        break;
    }
    return RT_EOK;
}
static rt_size_t sths34pf80_fetch_data(struct rt_sensor_device *sensor, void *buf, rt_size_t len)
{
    if (sensor->config.mode == RT_SENSOR_MODE_POLLING)
    {
        return _sths34pf80_polling_get_data(sensor, buf);
    }
    else if (sensor->config.mode == RT_SENSOR_MODE_INT)
    {
        return _sths34pf80_polling_get_data(sensor, buf);
    }
    else
    {
        return 0;
    }
}

static rt_err_t sths34pf80_control(struct rt_sensor_device *sensor, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    switch (cmd)
    {
    case RT_SENSOR_CTRL_GET_ID:
        STHS34PF80_ReadID(&sths34pf80, args);
        break;
    case RT_SENSOR_CTRL_SET_RANGE:
        result = -RT_ERROR;
        break;
    case RT_SENSOR_CTRL_SET_ODR:
        result = _sths34pf80_set_odr(sensor, (rt_uint32_t)args & 0xffff);
        break;
    case RT_SENSOR_CTRL_SET_MODE:
        result = _sths34pf80_set_mode(sensor, (rt_uint32_t)args & 0xff);
        break;
    case RT_SENSOR_CTRL_SET_POWER:
        result = -RT_ERROR;
        break;
    case RT_SENSOR_CTRL_SELF_TEST:
        result = -RT_ERROR;
        break;
    default:
        return -RT_ERROR;
    }
    return result;
}

static struct rt_sensor_ops sensor_ops =
{
    sths34pf80_fetch_data,
    sths34pf80_control
};

int rt_hw_sths34pf80_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor_presence = RT_NULL, sensor_temp = RT_NULL,sensor_motion = RT_NULL;
    struct rt_sensor_module *module = RT_NULL;

    module = rt_calloc(1, sizeof(struct rt_sensor_module));
    if (module == RT_NULL)
    {
        return -1;
    }
    {
        sensor_presence = rt_calloc(1, sizeof(struct rt_sensor_device));
        if (sensor_presence == RT_NULL)
            goto __exit;

        sensor_presence->info.type       = RT_SENSOR_CLASS_PROXIMITY;
        sensor_presence->info.vendor     = RT_SENSOR_VENDOR_STM;
        sensor_presence->info.model      = "sths34pf80_presence";
        sensor_presence->info.unit       = RT_SENSOR_UNIT_CM;
        sensor_presence->info.intf_type  = RT_SENSOR_INTF_I2C;

        rt_memcpy(&sensor_presence->config, cfg, sizeof(struct rt_sensor_config));
        sensor_presence->ops = &sensor_ops;
        sensor_presence->module = module;

        result = rt_hw_sensor_register(sensor_presence, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, RT_NULL);
        if (result != RT_EOK)
        {
            LOG_E("device register err code: %d", result);
            goto __exit;
        }
    }
    {
        sensor_temp = rt_calloc(1, sizeof(struct rt_sensor_device));
        if (sensor_temp == RT_NULL)
            return -1;

        sensor_temp->info.type       = RT_SENSOR_CLASS_TEMP;
        sensor_temp->info.vendor     = RT_SENSOR_VENDOR_STM;
        sensor_temp->info.model      = "sths34pf80_temp";
        sensor_temp->info.unit       = RT_SENSOR_UNIT_DCELSIUS;
        sensor_temp->info.intf_type  = RT_SENSOR_INTF_I2C;

        rt_memcpy(&sensor_temp->config, cfg, sizeof(struct rt_sensor_config));
        sensor_temp->ops = &sensor_ops;
        sensor_temp->module = module;

        result = rt_hw_sensor_register(sensor_temp, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, RT_NULL);
        if (result != RT_EOK)
        {
            LOG_E("device register err code: %d", result);
            goto __exit;
        }
    }
    {
        sensor_motion = rt_calloc(1, sizeof(struct rt_sensor_device));
        if (sensor_motion == RT_NULL)
            return -1;

        sensor_motion->info.type       = RT_SENSOR_CLASS_FORCE;
        sensor_motion->info.vendor     = RT_SENSOR_VENDOR_STM;
        sensor_motion->info.model      = "sths34pf80_motion";
        sensor_motion->info.unit       = RT_SENSOR_UNIT_MN;
        sensor_motion->info.intf_type  = RT_SENSOR_INTF_I2C;

        rt_memcpy(&sensor_motion->config, cfg, sizeof(struct rt_sensor_config));
        sensor_motion->ops = &sensor_ops;
        sensor_motion->module = module;

        result = rt_hw_sensor_register(sensor_motion, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,RT_NULL);
        if (result != RT_EOK)
        {
            LOG_E("device register err code: %d", result);
            goto __exit;
        }
    }

    module->sen[0] = sensor_presence;
    module->sen[1] = sensor_temp;
    module->sen[2] = sensor_motion;
    module->sen_num = 3;

    if(_sths34pf80_init(&cfg->intf) != RT_EOK)
    {
        LOG_E("sensor init failed");
        goto __exit;
    }

    LOG_I("sensor init success");
    return RT_EOK;

__exit:
    if(sensor_presence)
    {
        rt_device_unregister(&sensor_presence->parent);
        rt_free(sensor_presence);
    }
    if(sensor_temp)
    {
        rt_device_unregister(&sensor_temp->parent);
        rt_free(sensor_temp);
    }
    if(sensor_motion)
    {
        rt_device_unregister(&sensor_motion->parent);
        rt_free(sensor_motion);
    }
    if (module)
        rt_free(module);

    return -RT_ERROR;
}
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
