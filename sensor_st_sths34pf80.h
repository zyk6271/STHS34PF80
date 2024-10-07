/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     Rick       the first version
 */
#ifndef APPLICATIONS_SENSOR_ST_S34F80_H_
#define APPLICATIONS_SENSOR_ST_S34F80_H_
#include "rtthread.h"
#include "rtdevice.h"
#include "stdint.h"
#include "sths34pf80.h"
#include <rtdbg.h>

int rt_hw_sths34pf80_init(const char *name, struct rt_sensor_config *cfg);



#endif /* APPLICATIONS_SENSOR_ST_S34F80_H_ */
