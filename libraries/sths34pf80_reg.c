/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     Rick       the first version
 */
#include "rtthread.h"
#include "sths34pf80_reg.h"
/**
  * @brief  Read generic device register
  *
  * @param  sths34pf80_ctx_t* ctx: read / write interface definitions
  * @param  uint8_t reg: register to read
  * @param  uint8_t* data: pointer to buffer that store the data read
  * @param  uint16_t len: number of consecutive register to read
  *
  */
int32_t sths34pf80_read_reg(sths34pf80_ctx_t *ctx, uint8_t reg, uint8_t *data,
                         uint16_t len)
{
    int32_t ret;
    ret = ctx->read_reg(ctx->handle, reg, data, len);
    return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  sths34pf80_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t reg: register to write
  * @param  uint8_t* data: pointer to data to write in register reg
  * @param  uint16_t len: number of consecutive register to write
  *
*/
int32_t sths34pf80_write_reg(sths34pf80_ctx_t *ctx, uint8_t reg, uint8_t *data,
                          uint16_t len)
{
    int32_t ret;
    ret = ctx->write_reg(ctx->handle, reg, data, len);
    return ret;
}

/**
  * @brief  Low-pass filter configuration for motion and presence detection
*/
int32_t sths34pf80_lpf_presence_motion_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.lpf1.lpf_p_m = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF1, &(reg.byte), 1);
    }
    return ret;
}
int32_t sths34pf80_lpf_presence_motion_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, &(reg.byte), 1);
  *val = reg.lpf1.lpf_p_m;

  return ret;
}

/**
  * @brief  Low-pass filter configuration for motion detection
*/
int32_t sths34pf80_lpf_motion_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.lpf1.lpf_m = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF1, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_lpf_motion_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, &(reg.byte), 1);
  *val = reg.lpf1.lpf_m;

  return ret;
}

/**
  * @brief  Low-pass filter configuration for presence detection
*/
int32_t sths34pf80_lpf_presence_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.lpf2.lpf_p = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF2, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_lpf_presence_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, &(reg.byte), 1);
  *val = reg.lpf2.lpf_p;

  return ret;
}

/**
  * @brief  Low-pass filter configuration for ambient temperature
*/
int32_t sths34pf80_lpf_temperature_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.lpf2.lpf_a_t = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF2, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_lpf_temperature_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, &(reg.byte), 1);
  *val = reg.lpf2.lpf_a_t;

  return ret;
}

/**
  * @brief  Device identification
*/
int32_t sths34pf80_who_am_i_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_WHO_AM_I, &(reg.byte), 1);
  *val = reg.byte;

  return ret;
}

/**
  * @brief  Select the number of averages for ambient temperature
*/
int32_t sths34pf80_avg_trim_avg_t_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.avg_trim.avg_t = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_AVG_TRIM, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_avg_trim_avg_t_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, &(reg.byte), 1);
  *val = reg.avg_trim.avg_t;

  return ret;
}

/**
  * @brief  Select the number of averages for object temperature
*/
int32_t sths34pf80_avg_trim_avg_tmos_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.avg_trim.avg_tmos = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_AVG_TRIM, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_avg_trim_avg_tmos_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, &(reg.byte), 1);
  *val = reg.avg_trim.avg_tmos;

  return ret;
}

/**
  * @brief  Block data update for output registers TOBJECT (26h and 27h) and TAMBIENT (28h and 29h)
*/
int32_t sths34pf80_ctrl1_bdu_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg1.bdu = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL1, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl1_bdu_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, &(reg.byte), 1);
  *val = reg.ctrl_reg1.bdu;

  return ret;
}

/**
  * @brief  Output data rate
*/
int32_t sths34pf80_ctrl1_odr_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg1.odr = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL1, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl1_odr_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, &(reg.byte), 1);
  *val = reg.ctrl_reg1.odr;

  return ret;
}

/**
  * @brief  Reboot OTP memory content. Self-clearing upon completion. Default value : 0
*/
int32_t sths34pf80_ctrl2_boot_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg2.boot = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl2_boot_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.boot;

  return ret;
}

/**
  * @brief  Enable access to the registers(1) for embedded functions. Default value : 0
*/
int32_t sths34pf80_ctrl2_func_cfg_access_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg2.func_cfg_access = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl2_func_cfg_access_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.func_cfg_access;

  return ret;
}

/**
  * @brief  Enable ONE_SHOT
*/
int32_t sths34pf80_ctrl2_one_shot_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg2.one_shot = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl2_one_shot_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.one_shot;

  return ret;
}

/**
  * @brief  Interrupt active-high & active-low. Default value: 0
*/
int32_t sths34pf80_ctrl3_int_h_l_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg3.int_h_l = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl3_int_h_l_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.int_h_l;

  return ret;
}

/**
  * @brief  Interrupt masks for flag of FUNC_STATUS (25h)
*/
int32_t sths34pf80_ctrl3_int_msk0_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg3.int_msk0 = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl3_int_msk0_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.int_msk0;

  return ret;
}

int32_t sths34pf80_ctrl3_int_msk1_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg3.int_msk1 = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl3_int_msk1_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.int_msk1;

  return ret;
}

int32_t sths34pf80_ctrl3_int_msk2_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg3.int_msk2 = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl3_int_msk2_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.int_msk2;

  return ret;
}


/**
  * @brief  Push-pull / open-drain selection on the INT pin. Default value: 0
*/
int32_t sths34pf80_ctrl3_pp_od_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg3.pp_od = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl3_pp_od_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.pp_od;

  return ret;
}

/**
  * @brief  Configure the signal routed to the INT pin
*/
int32_t sths34pf80_ctrl3_ien_set(sths34pf80_ctx_t *ctx, uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg3.ien = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_ctrl3_ien_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.ien;

  return ret;
}

/**
  * @brief  Data ready for TAMB, TOBJ, TAMB_SHOCK, TPRESENCE, TMOTION.
  * @brief  This bit is reset to 0 when reading the FUNC_STATUS (25h)register.
*/

int32_t sths34pf80_drdy_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_STATUS, &(reg.byte), 1);
  *val = reg.status.drdy;

  return ret;
}

/**
  * @brief  Presence detection flag. This bit is reset to 0 when reading the FUNC_STATUS (25h) register
  * @brief  Motion detection flag. This bit is reset to 0 when reading the FUNC_STATUS (25h) register
  * @brief  Ambient temperature shock detection flag. This bit is reset to 0 when reading the FUNC_STATUS (25h) register
*/

int32_t sths34pf80_pres_flag_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_FUNC_STATUS, &(reg.byte), 1);
  *val = reg.func_status.pres_flag;

  return ret;
}
int32_t sths34pf80_mot_flag_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_FUNC_STATUS, &(reg.byte), 1);
  *val = reg.func_status.mot_flag;

  return ret;
}
int32_t sths34pf80_tamb_shock_flag_get(sths34pf80_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_reg_t reg;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_FUNC_STATUS, &(reg.byte), 1);
  *val = reg.func_status.tamb_shock_flag;

  return ret;
}

/**
  * @brief  The TOBJECT (object temperature) output value is 16-bit data that contains the measured
  * temperature of the object. It is composed of TOBJECT_H (27h) and TOBJECT_L (28h). The value is
  * expressed as 2’s complement and its sensitivity is 2000 LSB/°C.
*/

int32_t sths34pf80_tobject_get(sths34pf80_ctx_t *ctx, uint16_t *val)
{
  int32_t ret;
  uint8_t buf[2];

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TOBJECT_L, buf, 2);
  if( ret == RT_EOK )
  {
      *val = buf[1]<<8 | buf[0];
  }

  return ret;
}

/**
  * @brief  The TAMBIENT (ambient temperature) output value is 16-bit data that contains the ambient
  *  temperature. It is composed of TAMBIENT_H (28h) and TAMBIENT_L (29h). The value is expressed
  *  as 2’s complement and its sensitivity is 100 LSB/°C.
*/

int32_t sths34pf80_tambient_get(sths34pf80_ctx_t *ctx, uint16_t *val)
{
  int32_t ret;
  uint8_t buf[2];

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TAMBIENT_L, buf, 2);
  if( ret == RT_EOK )
  {
      *val = buf[1]<<8 | buf[0];
  }

  return ret;
}

/**
  * @brief  The TPRESENCE (presence) output value is 16-bit data that contains the presence data. It is
  * composed of TPRESENCE_H (3Bh) and TPRESENCE_L (3Ah). The value is expressed as 2’s complement.
*/

int32_t sths34pf80_tpresence_get(sths34pf80_ctx_t *ctx, uint16_t *val)
{
  int32_t ret;
  uint8_t buf[2];

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TPRESENCE_L, buf, 2);
  if( ret == RT_EOK )
  {
      *val = buf[1]<<8 | buf[0];
  }

  return ret;
}

/**
  * @brief  The TMOTION (motion) output value is 16-bit data that contains the motion data. It is composed
  * of TMOTION_H (3Dh) and TMOTION_L (3Ch). The value is expressed as 2’s complement
*/

int32_t sths34pf80_tmotion_get(sths34pf80_ctx_t *ctx, uint16_t *val)
{
  int32_t ret;
  uint8_t buf[2];

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TMOTION_L, buf, 2);
  if( ret == RT_EOK )
  {
      *val = buf[1]<<8 | buf[0];
  }

  return ret;
}

/**
  * @brief  The TAMB_SHOCK (ambient temperature shock) output value is 16-bit data that contains the ambient
  * temperature shock data. It is composed of TAMB_SHOCK_H (3Fh) and TAMB_SHOCK_L (3Eh). The value is expressed as 2’s complement
*/

int32_t sths34pf80_tamb_shock_get(sths34pf80_ctx_t *ctx, uint16_t *val)
{
  int32_t ret;
  uint8_t buf[2];

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TAMB_SHOCK_L, buf, 2);
  if( ret == RT_EOK )
  {
      *val = buf[1]<<8 | buf[0];
  }

  return ret;
}

/**
  * @brief  Threshold for detection algorithms. This value is 15-bit unsigned
*/
int32_t sths34pf80_threshold_set(sths34pf80_ctx_t *ctx,uint8_t addr,uint8_t val)
{
    sths34pf80_reg_t reg;
    int32_t ret;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg2.func_cfg_access = 1;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.byte = 0x40;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.byte = addr;
        ret = sths34pf80_write_reg(ctx,STHS34PF80_FUNC_CFG_ADDR , &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.byte = val;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_FUNC_CFG_DATA, &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.byte = 0;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.ctrl_reg2.func_cfg_access = 0;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    }
    return ret;
}

int32_t sths34pf80_threshold_get(sths34pf80_ctx_t *ctx,uint8_t addr,uint8_t *val)
{
    sths34pf80_reg_t reg;
    int32_t ret;
    uint8_t raw;

    ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    if (ret == RT_EOK)
    {
        reg.ctrl_reg2.func_cfg_access = 1;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.byte = 0x20;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.byte = addr;
        ret = sths34pf80_write_reg(ctx,STHS34PF80_FUNC_CFG_ADDR , &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        ret = sths34pf80_read_reg(ctx, STHS34PF80_FUNC_CFG_DATA, &raw, 1);
    }
    if (ret == RT_EOK)
    {
        reg.byte = 0;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, &(reg.byte), 1);
    }
    if (ret == RT_EOK)
    {
        reg.ctrl_reg2.func_cfg_access = 0;
        ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, &(reg.byte), 1);
    }

    *val = raw;

    return ret;
}
