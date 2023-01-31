/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     Rick       the first version
 */
#ifndef STHS34PF80_REG_H_
#define STHS34PF80_REG_H_

#include <stdint.h>

typedef int32_t (*sths34pf80_write_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef int32_t (*sths34pf80_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct
{
  /** Component mandatory fields **/
  sths34pf80_write_ptr  write_reg;
  sths34pf80_read_ptr   read_reg;
  /** Customizable optional pointer **/
  void *handle;
} sths34pf80_ctx_t;

#define STHS34PF80_FUNC_CFG_ADDR   0X08
#define STHS34PF80_FUNC_CFG_DATA   0X09
#define STHS34PF80_PRESENCE_THS_L  0X20
#define STHS34PF80_PRESENCE_THS_H  0X21
#define STHS34PF80_MOTION_THS_L    0X22
#define STHS34PF80_MOTION_THS_H    0X23
#define STHS34PF80_TAMBSHOCK_THS_L 0X24
#define STHS34PF80_TAMBSHOCK_THS_H 0X25
#define STHS34PF80_PAGE_RW         0X11
#define STHS34PF80_LPF1            0X0C
#define STHS34PF80_LPF2            0X0D
#define STHS34PF80_WHO_AM_I        0X0F
#define STHS34PF80_AVG_TRIM        0X10
#define STHS34PF80_PAGE_RW         0X11
#define STHS34PF80_CTRL1           0x20
#define STHS34PF80_CTRL2           0x21
#define STHS34PF80_CTRL3           0x22
#define STHS34PF80_STATUS          0x23
#define STHS34PF80_FUNC_STATUS     0x25
#define STHS34PF80_TOBJECT_L       0x26
#define STHS34PF80_TOBJECT_H       0x27
#define STHS34PF80_TAMBIENT_L      0x28
#define STHS34PF80_TAMBIENT_H      0x29
#define STHS34PF80_TPRESENCE_L     0x3A
#define STHS34PF80_TPRESENCE_H     0x3B
#define STHS34PF80_TMOTION_L       0x3C
#define STHS34PF80_TMOTION_H       0x3D
#define STHS34PF80_TAMB_SHOCK_L    0x3E
#define STHS34PF80_TAMB_SHOCK_H    0x3F

typedef struct
{
    uint8_t not_used1        : 5;
    uint8_t func_cfg_read    : 1;
    uint8_t func_cfg_write   : 1;
    uint8_t not_used2        : 1;
} sths34pf80_page_rw_t;

typedef struct
{
    uint8_t lpf_m            : 3;
    uint8_t lpf_p_m          : 3;
    uint8_t not_used1        : 2;
} sths34pf80_lpf1_t;

typedef struct
{
    uint8_t lpf_a_t          : 3;
    uint8_t lpf_p            : 3;
    uint8_t not_used         : 2;
} sths34pf80_lpf2_t;

typedef struct
{
    uint8_t avg_tmos         : 3;
    uint8_t not_used1        : 1;
    uint8_t avg_t            : 2;
    uint8_t not_used2        : 2;
} sths34pf80_avg_trim_t;

typedef struct
{
    uint8_t odr              : 4;
    uint8_t bdu              : 1;
    uint8_t not_used1        : 3;
} sths34pf80_ctrl1_t;

typedef struct
{
    uint8_t one_shot         : 1;
    uint8_t not_used1        : 3;
    uint8_t func_cfg_access  : 1;
    uint8_t not_used2        : 2;
    uint8_t boot             : 1;
} sths34pf80_ctrl2_t;

typedef struct
{
    uint8_t ien              : 2;
    uint8_t not_used1        : 1;
    uint8_t int_msk0         : 1;
    uint8_t int_msk1         : 1;
    uint8_t int_msk2         : 1;
    uint8_t pp_od            : 1;
    uint8_t int_h_l          : 1;
} sths34pf80_ctrl3_t;

typedef struct
{
    uint8_t not_used1        : 2;
    uint8_t drdy             : 1;
    uint8_t not_used2        : 5;
} sths34pf80_status_t;

typedef struct
{
    uint8_t tamb_shock_flag  : 1;
    uint8_t mot_flag         : 1;
    uint8_t pres_flag        : 1;
    uint8_t not_used1        : 5;
} sths34pf80_func_status_t;

typedef struct
{
    uint8_t bit0       : 1;
    uint8_t bit1       : 1;
    uint8_t bit2       : 1;
    uint8_t bit3       : 1;
    uint8_t bit4       : 1;
    uint8_t bit5       : 1;
    uint8_t bit6       : 1;
    uint8_t bit7       : 1;
} bitwise_t;

typedef union
{
    sths34pf80_page_rw_t       page_rw;
    sths34pf80_lpf1_t          lpf1;
    sths34pf80_lpf2_t          lpf2;
    sths34pf80_avg_trim_t      avg_trim;
    sths34pf80_ctrl1_t         ctrl_reg1;
    sths34pf80_ctrl2_t         ctrl_reg2;
    sths34pf80_ctrl3_t         ctrl_reg3;
    sths34pf80_status_t        status;
    sths34pf80_func_status_t   func_status;
    bitwise_t                  bitwise;
    uint8_t                    byte;
} sths34pf80_reg_t;

#endif /* APPLICATIONS_STHS34PF80_REG_H_ */
