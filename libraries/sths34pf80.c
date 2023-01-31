/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     Rick       the first version
 */
#include "stdint.h"
#include "sths34pf80.h"

/** @defgroup STHS34PF80_Private_Function_Prototypes STHS34PF80 Private Function Prototypes
 * @{
 */

static int32_t ReadRegWrap(void *Handle, uint8_t Reg, uint8_t *pData, uint16_t Length);
static int32_t WriteRegWrap(void *Handle, uint8_t Reg, uint8_t *pData, uint16_t Length);
static int32_t STHS34PF80_Initialize(STHS34PF80_Object_t *pObj);

/**
 * @brief  Wrap Read register component function to Bus IO function
 * @param  Handle the device handler
 * @param  Reg the register address
 * @param  pData the stored data pointer
 * @param  Length the length
 * @retval 0 in case of success, an error code otherwise
 */
static int32_t ReadRegWrap(void *Handle, uint8_t Reg, uint8_t *pData, uint16_t Length)
{
  uint16_t i;
  int32_t ret = STHS34PF80_OK;
  STHS34PF80_Object_t *pObj = (STHS34PF80_Object_t *)Handle;

  if (pObj->IO.BusType == STHS34PF80_I2C_BUS) /* I2C */
  {
    for (i = 0; i < Length; i++)
    {
      ret = pObj->IO.ReadReg(pObj->IO.Address, (Reg + i), &pData[i], 1);
      if (ret != STHS34PF80_OK)
      {
        return STHS34PF80_ERROR;
      }
    }

    return ret;
  }
  else /* SPI 4-Wires or SPI 3-Wires */
  {
    return pObj->IO.ReadReg(pObj->IO.Address, Reg, pData, Length);
  }
}

/**
 * @brief  Wrap Write register component function to Bus IO function
 * @param  Handle the device handler
 * @param  Reg the register address
 * @param  pData the stored data pointer
 * @param  Length the length
 * @retval 0 in case of success, an error code otherwise
 */
static int32_t WriteRegWrap(void *Handle, uint8_t Reg, uint8_t *pData, uint16_t Length)
{
  uint16_t i;
  int32_t ret = STHS34PF80_OK;
  STHS34PF80_Object_t *pObj = (STHS34PF80_Object_t *)Handle;

  if (pObj->IO.BusType == STHS34PF80_I2C_BUS) /* I2C */
  {
    for (i = 0; i < Length; i++)
    {
      ret = pObj->IO.WriteReg(pObj->IO.Address, (Reg + i), &pData[i], 1);
      if (ret != STHS34PF80_OK)
      {
        return STHS34PF80_ERROR;
      }
    }

    return ret;
  }
  else /* SPI 4-Wires or SPI 3-Wires */
  {
    return pObj->IO.WriteReg(pObj->IO.Address, Reg, pData, Length);
  }
}

/**
 * @brief  Register Component Bus IO operations
 * @param  pObj the device pObj
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_RegisterBusIO(STHS34PF80_Object_t *pObj, STHS34PF80_IO_t *pIO)
{
  int32_t ret = STHS34PF80_OK;

  if (pObj == NULL)
  {
    ret = STHS34PF80_ERROR;
  }
  else
  {
    pObj->IO.Init      = pIO->Init;
    pObj->IO.DeInit    = pIO->DeInit;
    pObj->IO.BusType   = pIO->BusType;
    pObj->IO.Address   = pIO->Address;
    pObj->IO.WriteReg  = pIO->WriteReg;
    pObj->IO.ReadReg   = pIO->ReadReg;
    pObj->IO.GetTick   = pIO->GetTick;

    pObj->Ctx.read_reg  = ReadRegWrap;
    pObj->Ctx.write_reg = WriteRegWrap;
    pObj->Ctx.handle   = pObj;
  }

  return ret;
}

/**
 * @brief  Initialize the STHS34PF80 sensor
 * @param  pObj the device pObj
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_Init(STHS34PF80_Object_t *pObj)
{
  if (pObj->is_initialized == 0U)
  {
    if (STHS34PF80_Initialize(pObj) != STHS34PF80_OK)
    {
      return STHS34PF80_ERROR;
    }
  }

  pObj->is_initialized = 1U;

  return STHS34PF80_OK;
}

/**
 * @brief  Deinitialize the STHS34PF80 sensor
 * @param  pObj the device pObj
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_DeInit(STHS34PF80_Object_t *pObj)
{
    if (sths34pf80_ctrl1_odr_set(&(pObj->Ctx), 0) != STHS34PF80_OK)
    {
      return STHS34PF80_ERROR;
    }

    pObj->is_initialized = 0;

    return STHS34PF80_OK;
}

/**
 * @brief  Get WHO_AM_I value
 * @param  pObj the device pObj
 * @param  Id the WHO_AM_I value
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ReadID(STHS34PF80_Object_t *pObj, uint8_t *Id)
{
  if (sths34pf80_who_am_i_get(&(pObj->Ctx), Id) != STHS34PF80_OK)
  {
    return STHS34PF80_ERROR;
  }
  return STHS34PF80_OK;
}
/**
 * @brief  Initialize the STHS34PF80 sensor
 * @param  pObj the device pObj
 * @retval 0 in case of success, an error code otherwise
 */
static int32_t STHS34PF80_Initialize(STHS34PF80_Object_t *pObj)
{
    if (sths34pf80_lpf_motion_set(&(pObj->Ctx), pObj->Config.LPF_Motion) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_lpf_presence_set(&(pObj->Ctx), pObj->Config.LPF_Presence) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_lpf_temperature_set(&(pObj->Ctx), pObj->Config.LPF_Temperature) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_avg_trim_avg_tmos_set(&(pObj->Ctx), pObj->Config.AVG_TMOS) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_ctrl1_odr_set(&(pObj->Ctx), pObj->Config.ODR) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_threshold_set(&(pObj->Ctx),STHS34PF80_PRESENCE_THS_L,pObj->Config.THS_Presence & 0xFF) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_threshold_set(&(pObj->Ctx),STHS34PF80_PRESENCE_THS_H,(pObj->Config.THS_Presence & 0xFF00)>>8) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_threshold_set(&(pObj->Ctx),STHS34PF80_MOTION_THS_L,pObj->Config.THS_Motion & 0xFF) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_threshold_set(&(pObj->Ctx),STHS34PF80_MOTION_THS_H,(pObj->Config.THS_Motion & 0xFF00)>>8) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_threshold_set(&(pObj->Ctx),STHS34PF80_TAMBSHOCK_THS_L,pObj->Config.THS_Temp_Shock & 0xFF) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    if (sths34pf80_threshold_set(&(pObj->Ctx),STHS34PF80_TAMBSHOCK_THS_H,(pObj->Config.THS_Temp_Shock & 0xFF00)>>8) != STHS34PF80_OK)
    {
        return STHS34PF80_ERROR;
    }
    return STHS34PF80_OK;
}

/**
 * @brief  Get the STHS34PF80 Presence value
 * @param  pObj the device pObj
 * @param  Value pointer where the Presence value is written
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ReadPresence(STHS34PF80_Object_t *pObj, uint16_t *value)
{
  uint32_t data_raw_presence = 0;

  if (sths34pf80_tpresence_get(&(pObj->Ctx), &data_raw_presence) != STHS34PF80_OK)
  {
    return STHS34PF80_ERROR;
  }

  *value = data_raw_presence;

  return STHS34PF80_OK;
}

/**
 * @brief  Get the STHS34PF80 Presence flag
 * @param  pObj the device pObj
 * @param  Value pointer where the Presence value is written
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ReadPresenceFlag(STHS34PF80_Object_t *pObj, uint16_t *value)
{
  uint32_t data_raw_flag = 0;

  if (sths34pf80_pres_flag_get(&(pObj->Ctx), &data_raw_flag) != STHS34PF80_OK)
  {
    return STHS34PF80_ERROR;
  }

  *value = data_raw_flag;

  return STHS34PF80_OK;
}

/**
 * @brief  Get the STHS34PF80 temp value
 * @param  pObj the device pObj
 * @param  Value pointer where the temp value is written
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ReadTemperature(STHS34PF80_Object_t *pObj, uint16_t *value)
{
  uint32_t data_raw_temp = 0;

  if (sths34pf80_tambient_get(&(pObj->Ctx), &data_raw_temp) != STHS34PF80_OK)
  {
    return STHS34PF80_ERROR;
  }

  *value = data_raw_temp;

  return STHS34PF80_OK;
}

/**
 * @brief  Get the STHS34PF80 Temp_Shock flag
 * @param  pObj the device pObj
 * @param  Value pointer where the temp value is written
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ReadTempShockFlag(STHS34PF80_Object_t *pObj, uint16_t *value)
{
  uint32_t data_raw_flag = 0;

  if (sths34pf80_tamb_shock_flag_get(&(pObj->Ctx), &data_raw_flag) != STHS34PF80_OK)
  {
    return STHS34PF80_ERROR;
  }

  *value = data_raw_flag;

  return STHS34PF80_OK;
}



/**
 * @brief  Get the STHS34PF80 Motion value
 * @param  pObj the device pObj
 * @param  Value pointer where the pressure value is written
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ReadMotion(STHS34PF80_Object_t *pObj, uint16_t *value)
{
  uint32_t data_raw_motion = 0;

  if (sths34pf80_tmotion_get(&(pObj->Ctx), &data_raw_motion) != STHS34PF80_OK)
  {
    return STHS34PF80_ERROR;
  }

  *value = data_raw_motion;

  return STHS34PF80_OK;
}

/**
 * @brief  Get the STHS34PF80 Motion flag
 * @param  pObj the device pObj
 * @param  Value pointer where the temp value is written
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ReadMotionFlag(STHS34PF80_Object_t *pObj, uint16_t *value)
{
  uint32_t data_raw_flag = 0;

  if (sths34pf80_mot_flag_get(&(pObj->Ctx), &data_raw_flag) != STHS34PF80_OK)
  {
    return STHS34PF80_ERROR;
  }

  *value = data_raw_flag;

  return STHS34PF80_OK;
}

/**
 * @brief  STHS34PF80_ControlINT
 * @param  pObj the device pObj
 * @param  msk_id is INT mask select(presence-motion-tamb_shock--->000),state is control value
 * @retval 0 in case of success, an error code otherwise
 */
int32_t STHS34PF80_ControlINT(STHS34PF80_Object_t *pObj, uint8_t msk_id, uint8_t state)
{
    sths34pf80_ctrl3_ien_set(&(pObj->Ctx), 0x02);
    switch(msk_id)
    {
    case 0:
        sths34pf80_ctrl3_int_msk0_set(&(pObj->Ctx), state);
        break;
    case 1:
        sths34pf80_ctrl3_int_msk1_set(&(pObj->Ctx), state);
        break;
    case 2:
        sths34pf80_ctrl3_int_msk2_set(&(pObj->Ctx), state);
        break;
    default:
        break;
    }
    return STHS34PF80_OK;
}
