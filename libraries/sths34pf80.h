/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     Rick       the first version
 */
#ifndef APPLICATIONS_STHS34PF80_H_
#define APPLICATIONS_STHS34PF80_H_

#include "sths34pf80_reg.h"
#include <string.h>

typedef int32_t (*STHS34PF80_Init_Func)(void);
typedef int32_t (*STHS34PF80_DeInit_Func)(void);
typedef int32_t (*STHS34PF80_GetTick_Func)(void);
typedef int32_t (*STHS34PF80_WriteReg_Func)(uint16_t, uint16_t, uint8_t *, uint16_t);
typedef int32_t (*STHS34PF80_ReadReg_Func)(uint16_t, uint16_t, uint8_t *, uint16_t);

typedef struct
{
    STHS34PF80_Init_Func          Init;
    STHS34PF80_DeInit_Func        DeInit;
    uint32_t                      BusType;
    uint8_t                       Address;
    STHS34PF80_WriteReg_Func      WriteReg;
    STHS34PF80_ReadReg_Func       ReadReg;
    STHS34PF80_GetTick_Func       GetTick;
} STHS34PF80_IO_t;

typedef struct
{
    uint8_t     LPF_Motion;
    uint8_t     LPF_Presence;
    uint8_t     LPF_Temperature;
    uint8_t     AVG_TMOS;
    uint8_t     ODR;
    uint16_t    THS_Motion;
    uint16_t    THS_Presence;
    uint16_t    THS_Temp_Shock;
} STHS34PF80_Config_t;

typedef struct
{
    STHS34PF80_IO_t        IO;
    sths34pf80_ctx_t       Ctx;
    STHS34PF80_Config_t    Config;
    uint8_t             is_initialized;
} STHS34PF80_Object_t;

/**
 * @}
 */

/** @defgroup STHS34PF80_Exported_Constants STHS34PF80 Exported Constants
 * @{
 */

#define STHS34PF80_OK                0
#define STHS34PF80_ERROR            -1

#define STHS34PF80_I2C_BUS          0U

#endif /* APPLICATIONS_STHS34PF80_H_ */
