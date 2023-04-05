/****************************************************************************
 * include/nuttx/analog/ads1299.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_ANALOG_ADS129X_H
#define __INCLUDE_NUTTX_ANALOG_ADS129X_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>
#include <nuttx/spi/spi.h>

#if defined(CONFIG_SPI) && defined(CONFIG_ADC_ADS129X)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

// ADS1299 defines

/*
    This file is mainly oriented on the ADS1299 and derivatives.
    ADS1298-only constants are prefixed with ADS1298_

 */

enum spi_command {
    // system commands
    WAKEUP = 0x02,
    STANDBY = 0x04,
    RESET = 0x06,
    START = 0x08,
    STOP = 0x0a,

    // read commands
            RDATAC = 0x10,
    SDATAC = 0x11,
    RDATA = 0x12,

    // register commands
    RREG = 0x20,
    WREG = 0x40
};

enum reg {
    // device settings
    ID = 0x00,

    // global settings
    CONFIG1 = 0x01,
    CONFIG2 = 0x02,
    CONFIG3 = 0x03,
    LOFF = 0x04,

    // channel specific settings
    CHnSET = 0x04,
    CH1SET = CHnSET + 1,
    CH2SET = CHnSET + 2,
    CH3SET = CHnSET + 3,
    CH4SET = CHnSET + 4,
    CH5SET = CHnSET + 5,
    CH6SET = CHnSET + 6,
    CH7SET = CHnSET + 7,
    CH8SET = CHnSET + 8,
    RLD_SENSP = 0x0d,
    RLD_SENSN = 0x0e,
    LOFF_SENSP = 0x0f,
    LOFF_SENSN = 0x10,
    LOFF_FLIP = 0x11,

    // lead off status
            LOFF_STATP = 0x12,
    LOFF_STATN = 0x13,

    // other
            GPIO = 0x14,
    PACE = 0x15,
    RESP = 0x16,
    CONFIG4 = 0x17,
    WCT1 = 0x18,
    WCT2 = 0x19
};

enum ID_bits {
    DEV_ID7 = 0x80,
    DEV_ID6 = 0x40,
    DEV_ID5 = 0x20,
    DEV_ID2 = 0x04,
    DEV_ID1 = 0x02,
    DEV_ID0 = 0x01,

    ID_const = 0x10,
    ID_ADS129x = DEV_ID7,
    ID_ADS129xR = (DEV_ID7 | DEV_ID6),

    ID_4CHAN = 0,
    ID_6CHAN = DEV_ID0,
    ID_8CHAN = DEV_ID1,

    ID_ADS1294 = (ID_ADS129x | ID_4CHAN),
    ID_ADS1296 = (ID_ADS129x | ID_6CHAN),
    ID_ADS1298 = (ID_ADS129x | ID_8CHAN),
    ID_ADS1294R = (ID_ADS129xR | ID_4CHAN),
    ID_ADS1296R = (ID_ADS129xR | ID_6CHAN),
    ID_ADS1298R = (ID_ADS129xR | ID_8CHAN)
};

enum CONFIG1_bits {
    HR = 0x80,
    DAISY_EN = 0x40,
    CLK_EN = 0x20,
    DR2 = 0x04,
    DR1 = 0x02,
    DR0 = 0x01,

    // correct for ADS1298/1294; incorrect for ADS1299
    // TODO: Fix for ADS1299

    // ADS1298
    //CONFIG1_const = 0x00,

    // ADS1299
    CONFIG1_const = 0xE0,

    // ADS1298
    /*
HIGH_RES_32k_SPS = HR,
HIGH_RES_16k_SPS = (HR | DR0),
HIGH_RES_8k_SPS = (HR | DR1),
HIGH_RES_4k_SPS = (HR | DR1 | DR0),
HIGH_RES_2k_SPS = (HR | DR2),
HIGH_RES_1k_SPS = (HR | DR2 | DR0),
HIGH_RES_500_SPS = (HR | DR2 | DR1),
LOW_POWR_250_SPS = (DR2 | DR1)
    */

    // ADS1299
    HIGH_RES_16k_SPS = HR,
    HIGH_RES_8k_SPS = (HR | DR0),
    HIGH_RES_4k_SPS = (HR | DR1),
    HIGH_RES_2k_SPS = (HR | DR1 | DR0),
    HIGH_RES_1k_SPS = (HR | DR2),
    HIGH_RES_500_SPS = (HR | DR2 | DR0),
    HIGH_RES_250_SPS = (HR | DR2 | DR1),

};

enum CONFIG2_bits {
    WCT_CHOP = 0x20,
    INT_TEST = 0x10,
    TEST_AMP = 0x04,
    TEST_FREQ1 = 0x02,
    TEST_FREQ0 = 0x01,

    // ADS1298
    //CONFIG2_const = 0x00,

    // ADS1299
    CONFIG2_const = 0xC0,

    INT_TEST_4HZ = INT_TEST,
    INT_TEST_8HZ = (INT_TEST | TEST_FREQ0),
    INT_TEST_DC = (INT_TEST | TEST_FREQ1 | TEST_FREQ0)
};

enum CONFIG3_bits {
    PD_REFBUF = 0x80,
    VREF_4V = 0x20,
    RLD_MEAS = 0x10,
    RLDREF_INT = 0x08,
    PD_RLD = 0x04,
    RLD_LOFF_SENS = 0x02,
    RLD_STAT = 0x01,

    // ADS1298
    //CONFIG3_const = 0x40

    // ADS1299
            CONFIG3_const = 0x60
};

enum LOFF_bits {
    COMP_TH2 = 0x80,
    COMP_TH1 = 0x40,
    COMP_TH0 = 0x20,
    VLEAD_OFF_EN = 0x10,
    ILEAD_OFF1 = 0x08,
    ILEAD_OFF0 = 0x04,
    FLEAD_OFF1 = 0x02,
    FLEAD_OFF0 = 0x01,

    LOFF_const = 0x00,

    COMP_TH_95 = 0x00,
    COMP_TH_92_5 = COMP_TH0,
    COMP_TH_90 = COMP_TH1,
    COMP_TH_87_5 = (COMP_TH1 | COMP_TH0),
    COMP_TH_85 = COMP_TH2,
    COMP_TH_80 = (COMP_TH2 | COMP_TH0),
    COMP_TH_75 = (COMP_TH2 | COMP_TH1),
    COMP_TH_70 = (COMP_TH2 | COMP_TH1 | COMP_TH0),

    ILEAD_OFF_6nA = 0x00,
    ILEAD_OFF_12nA = ILEAD_OFF0,
    ILEAD_OFF_18nA = ILEAD_OFF1,
    ILEAD_OFF_24nA = (ILEAD_OFF1 | ILEAD_OFF0),

    FLEAD_OFF_AC = FLEAD_OFF0,
    FLEAD_OFF_DC = (FLEAD_OFF1 | FLEAD_OFF0)
};

enum CHnSET_bits {
    PDn = 0x80,
    PD_n = 0x80,
    GAINn2 = 0x40,
    GAINn1 = 0x20,
    GAINn0 = 0x10,
    MUXn2 = 0x04,
    MUXn1 = 0x02,
    MUXn0 = 0x01,

    CHnSET_const = 0x00,

    // ADS1299
    GAIN_1X = 0x00,
    GAIN_2X = GAINn0,
    GAIN_4X = GAINn1,
    GAIN_6X = (GAINn1 | GAINn0),
    GAIN_8X = GAINn2,
    GAIN_12X = (GAINn2 | GAINn0),
    GAIN_24X = (GAINn2 | GAINn1),

    // ADS1298
    ADS1298_GAIN_1X = GAINn0,
    ADS1298_GAIN_2X = GAINn1,
    ADS1298_GAIN_3X = (GAINn1 | GAINn0),
    ADS1298_GAIN_4X = GAINn2,
    ADS1298_GAIN_6X = 0x00,
    ADS1298_GAIN_8X = (GAINn2 | GAINn0),
    ADS1298_GAIN_12X = (GAINn2 | GAINn1),

    ELECTRODE_INPUT = 0x00,
    SHORTED = MUXn0,
    RLD_INPUT = MUXn1,
    MVDD = (MUXn1 | MUXn0),
    TEMP = MUXn2,
    TEST_SIGNAL = (MUXn2 | MUXn0),
    RLD_DRP = (MUXn2 | MUXn1),
    RLD_DRN = (MUXn2 | MUXn1 | MUXn0)
};

enum CH1SET_bits {
    PD_1 = 0x80,
    GAIN12 = 0x40,
    GAIN11 = 0x20,
    GAIN10 = 0x10,
    MUX12 = 0x04,
    MUX11 = 0x02,
    MUX10 = 0x01,

    CH1SET_const = 0x00
};

enum CH2SET_bits {
    PD_2 = 0x80,
    GAIN22 = 0x40,
    GAIN21 = 0x20,
    GAIN20 = 0x10,
    MUX22 = 0x04,
    MUX21 = 0x02,
    MUX20 = 0x01,

    CH2SET_const = 0x00
};

enum CH3SET_bits {
    PD_3 = 0x80,
    GAIN32 = 0x40,
    GAIN31 = 0x20,
    GAIN30 = 0x10,
    MUX32 = 0x04,
    MUX31 = 0x02,
    MUX30 = 0x01,

    CH3SET_const = 0x00
};

enum CH4SET_bits {
    PD_4 = 0x80,
    GAIN42 = 0x40,
    GAIN41 = 0x20,
    GAIN40 = 0x10,
    MUX42 = 0x04,
    MUX41 = 0x02,
    MUX40 = 0x01,

    CH4SET_const = 0x00
};

enum CH5SET_bits {
    PD_5 = 0x80,
    GAIN52 = 0x40,
    GAIN51 = 0x20,
    GAIN50 = 0x10,
    MUX52 = 0x04,
    MUX51 = 0x02,
    MUX50 = 0x01,

    CH5SET_const = 0x00
};

enum CH6SET_bits {
    PD_6 = 0x80,
    GAIN62 = 0x40,
    GAIN61 = 0x20,
    GAIN60 = 0x10,
    MUX62 = 0x04,
    MUX61 = 0x02,
    MUX60 = 0x01,

    CH6SET_const = 0x00
};

enum CH7SET_bits {
    PD_7 = 0x80,
    GAIN72 = 0x40,
    GAIN71 = 0x20,
    GAIN70 = 0x10,
    MUX72 = 0x04,
    MUX71 = 0x02,
    MUX70 = 0x01,

    CH7SET_const = 0x00
};

enum CH8SET_bits {
    PD_8 = 0x80,
    GAIN82 = 0x40,
    GAIN81 = 0x20,
    GAIN80 = 0x10,
    MUX82 = 0x04,
    MUX81 = 0x02,
    MUX80 = 0x01,

    CH8SET_const = 0x00
};

enum RLD_SENSP_bits {
    RLD8P = 0x80,
    RLD7P = 0x40,
    RLD6P = 0x20,
    RLD5P = 0x10,
    RLD4P = 0x08,
    RLD3P = 0x04,
    RLD2P = 0x02,
    RLD1P = 0x01,

    RLD_SENSP_const = 0x00
};

enum RLD_SENSN_bits {
    RLD8N = 0x80,
    RLD7N = 0x40,
    RLD6N = 0x20,
    RLD5N = 0x10,
    RLD4N = 0x08,
    RLD3N = 0x04,
    RLD2N = 0x02,
    RLD1N = 0x01,

    RLD_SENSN_const = 0x00
};

enum LOFF_SENSP_bits {
    LOFF8P = 0x80,
    LOFF7P = 0x40,
    LOFF6P = 0x20,
    LOFF5P = 0x10,
    LOFF4P = 0x08,
    LOFF3P = 0x04,
    LOFF2P = 0x02,
    LOFF1P = 0x01,

    LOFF_SENSP_const = 0x00
};

enum LOFF_SENSN_bits {
    LOFF8N = 0x80,
    LOFF7N = 0x40,
    LOFF6N = 0x20,
    LOFF5N = 0x10,
    LOFF4N = 0x08,
    LOFF3N = 0x04,
    LOFF2N = 0x02,
    LOFF1N = 0x01,

    LOFF_SENSN_const = 0x00
};

enum LOFF_FLIP_bits {
    LOFF_FLIP8 = 0x80,
    LOFF_FLIP7 = 0x40,
    LOFF_FLIP6 = 0x20,
    LOFF_FLIP5 = 0x10,
    LOFF_FLIP4 = 0x08,
    LOFF_FLIP3 = 0x04,
    LOFF_FLIP2 = 0x02,
    LOFF_FLIP1 = 0x01,

    LOFF_FLIP_const = 0x00
};

enum LOFF_STATP_bits {
    IN8P_OFF = 0x80,
    IN7P_OFF = 0x40,
    IN6P_OFF = 0x20,
    IN5P_OFF = 0x10,
    IN4P_OFF = 0x08,
    IN3P_OFF = 0x04,
    IN2P_OFF = 0x02,
    IN1P_OFF = 0x01,

    LOFF_STATP_const = 0x00
};

enum LOFF_STATN_bits {
    IN8N_OFF = 0x80,
    IN7N_OFF = 0x40,
    IN6N_OFF = 0x20,
    IN5N_OFF = 0x10,
    IN4N_OFF = 0x08,
    IN3N_OFF = 0x04,
    IN2N_OFF = 0x02,
    IN1N_OFF = 0x01,

    LOFF_STATN_const = 0x00
};

enum GPIO_bits {
    GPIOD4 = 0x80,
    GPIOD3 = 0x40,
    GPIOD2 = 0x20,
    GPIOD1 = 0x10,
    GPIOC4 = 0x08,
    GPIOC3 = 0x04,
    GPIOC2 = 0x02,
    GPIOC1 = 0x01,

    GPIO_const = 0x00
};

enum PACE_bits {
    PACEE1 = 0x10,
    PACEE0 = 0x08,
    PACEO1 = 0x04,
    PACEO0 = 0x02,
    PD_PACE = 0x01,

    PACE_const = 0x00,

    PACEE_CHAN2 = 0x00,
    PACEE_CHAN4 = PACEE0,
    PACEE_CHAN6 = PACEE1,
    PACEE_CHAN8 = (PACEE1 | PACEE0),

    PACEO_CHAN1 = 0x00,
    PACEO_CHAN3 = PACEE0,
    PACEO_CHAN5 = PACEE1,
    PACEO_CHAN7 = (PACEE1 | PACEE0)
};

enum RESP_bits {
    RESP_DEMOD_EN1 = 0x80,
    RESP_MOD_EN1 = 0x40,
    RESP_PH2 = 0x10,
    RESP_PH1 = 0x08,
    RESP_PH0 = 0x04,
    RESP_CTRL1 = 0x02,
    RESP_CTRL0 = 0x01,

    RESP_const = 0x20,

    RESP_PH_22_5 = 0x00,
    RESP_PH_45 = RESP_PH0,
    RESP_PH_67_5 = RESP_PH1,
    RESP_PH_90 = (RESP_PH1 | RESP_PH0),
    RESP_PH_112_5 = RESP_PH2,
    RESP_PH_135 = (RESP_PH2 | RESP_PH0),
    RESP_PH_157_5 = (RESP_PH2 | RESP_PH1),

    RESP_NONE = 0x00,
    RESP_EXT = RESP_CTRL0,
    RESP_INT_SIG_INT = RESP_CTRL1,
    RESP_INT_SIG_EXT = (RESP_CTRL1 | RESP_CTRL0)
};

enum CONFIG4_bits {
    RESP_FREQ2 = 0x80,
    RESP_FREQ1 = 0x40,
    RESP_FREQ0 = 0x20,
    SINGLE_SHOT = 0x08,
    WCT_TO_RLD = 0x04,
    PD_LOFF_COMP = 0x02,

    CONFIG4_const = 0x00,

    RESP_FREQ_64k_Hz = 0x00,
    RESP_FREQ_32k_Hz = RESP_FREQ0,
    RESP_FREQ_16k_Hz = RESP_FREQ1,
    RESP_FREQ_8k_Hz = (RESP_FREQ1 | RESP_FREQ0),
    RESP_FREQ_4k_Hz = RESP_FREQ2,
    RESP_FREQ_2k_Hz = (RESP_FREQ2 | RESP_FREQ0),
    RESP_FREQ_1k_Hz = (RESP_FREQ2 | RESP_FREQ1),
    RESP_FREQ_500_Hz = (RESP_FREQ2 | RESP_FREQ1 | RESP_FREQ0)
};

enum WCT1_bits {
    aVF_CH6 = 0x80,
    aVL_CH5 = 0x40,
    aVR_CH7 = 0x20,
    avR_CH4 = 0x10,
    PD_WCTA = 0x08,
    WCTA2 = 0x04,
    WCTA1 = 0x02,
    WCTA0 = 0x01,

    WCT1_const = 0x00,

    WCTA_CH1P = 0x00,
    WCTA_CH1N = WCTA0,
    WCTA_CH2P = WCTA1,
    WCTA_CH2N = (WCTA1 | WCTA0),
    WCTA_CH3P = WCTA2,
    WCTA_CH3N = (WCTA2 | WCTA0),
    WCTA_CH4P = (WCTA2 | WCTA1),
    WCTA_CH4N = (WCTA2 | WCTA1 | WCTA0)
};

enum WCT2_bits {
    PD_WCTC = 0x80,
    PD_WCTB = 0x40,
    WCTB2 = 0x20,
    WCTB1 = 0x10,
    WCTB0 = 0x08,
    WCTC2 = 0x04,
    WCTC1 = 0x02,
    WCTC0 = 0x01,

    WCT2_const = 0x00,

    WCTB_CH1P = 0x00,
    WCTB_CH1N = WCTB0,
    WCTB_CH2P = WCTB1,
    WCTB_CH2N = (WCTB1 | WCTB0),
    WCTB_CH3P = WCTB2,
    WCTB_CH3N = (WCTB2 | WCTB0),
    WCTB_CH4P = (WCTB2 | WCTB1),
    WCTB_CH4N = (WCTB2 | WCTB1 | WCTB0),

    WCTC_CH1P = 0x00,
    WCTC_CH1N = WCTC0,
    WCTC_CH2P = WCTC1,
    WCTC_CH2N = (WCTC1 | WCTC0),
    WCTC_CH3P = WCTC2,
    WCTC_CH3N = (WCTC2 | WCTC0),
    WCTC_CH4P = (WCTC2 | WCTC1),
    WCTC_CH4N = (WCTC2 | WCTC1 | WCTC0)
};



/* IOCTL Commands ***********************************************************/

/* Cmd: ANIOC_ADS1299_READ                    Arg: uint32_t *value
 * Cmd: ANIOC_ADS1299_SET_GAIN                Arg: uint8_t value
 * Cmd: ANIOC_ADS1299_SET_POSITIVE_INPUT      Arg: uint8_t value
 * Cmd: ANIOC_ADS1299_SET_NEGATIVE_INPUT      Arg: uint8_t value
 * Cmd: ANIOC_ADS1299_IS_DATA_READY           Arg: bool *value
 * Cmd: ANIOC_ADS1299_DO_SYSTEM_OFFSET_CALIB  Arg: None
 */

#define ANIOC_ADS1299_READ                    _ANIOC(AN_ADS1299_FIRST + 0)
#define ANIOC_ADS1299_SET_GAIN                _ANIOC(AN_ADS1299_FIRST + 1)
#define ANIOC_ADS1299_SET_POSITIVE_INPUT      _ANIOC(AN_ADS1299_FIRST + 2)
#define ANIOC_ADS1299_SET_NEGATIVE_INPUT      _ANIOC(AN_ADS1299_FIRST + 3)
#define ANIOC_ADS1299_IS_DATA_READY           _ANIOC(AN_ADS1299_FIRST + 4)
#define ANIOC_ADS1299_DO_SYSTEM_OFFSET_CALIB  _ANIOC(AN_ADS1299_FIRST + 5)

/* ADS129X REGISTER *********************************************************/

// FIXME
#define ADS129X_REG_SETUP               (0x00)  /* Setup Register */
#define ADS129X_REG_MUX                 (0x01)  /* Multiplexer Control Register */
#define ADS129X_REG_ACR                 (0x02)  /* Analog Control Register */
#define ADS129X_REG_ODAC                (0x03)  /* Offset DAC */
#define ADS129X_REG_DIO                 (0x04)  /* Data I/O */
#define ADS129X_REG_DIR                 (0x05)  /* Direction Control for Data I/O */
#define ADS129X_REG_IOCON               (0x06)  /* I/O Configuration Register */

/* ADS129X REGISTER Bit Definitions *****************************************/

// FIXME
/* SETUP */
#define ADS129X_REG_SETUP_BIT_BOCS      (1 << 3)
#define ADS129X_REG_SETUP_BIT_PGA2      (1 << 2)
#define ADS129X_REG_SETUP_BIT_PGA1      (1 << 1)
#define ADS129X_REG_SETUP_BIT_PGA0      (1 << 0)
/* MUX */
#define ADS129X_REG_MUX_BIT_PSEL3       (1 << 7)
#define ADS129X_REG_MUX_BIT_PSEL2       (1 << 6)
#define ADS129X_REG_MUX_BIT_PSEL1       (1 << 5)
#define ADS129X_REG_MUX_BIT_PSEL0       (1 << 4)
#define ADS129X_REG_MUX_BIT_NSEL3       (1 << 3)
#define ADS129X_REG_MUX_BIT_NSEL2       (1 << 2)
#define ADS129X_REG_MUX_BIT_NSEL1       (1 << 1)
#define ADS129X_REG_MUX_BIT_NSEL0       (1 << 0)
/* ACR */
#define ADS129X_REG_ACR_BIT_NDRDY       (1 << 7)
#define ADS129X_REG_ACR_BIT_UnB         (1 << 6)
#define ADS129X_REG_ACR_BIT_SPEED       (1 << 5)
#define ADS129X_REG_ACR_BIT_BUFEN       (1 << 4)
#define ADS129X_REG_ACR_BIT_BITORDER    (1 << 3)
#define ADS129X_REG_ACR_BIT_RANGE       (1 << 2)
#define ADS129X_REG_ACR_BIT_DR1         (1 << 1)
#define ADS129X_REG_ACR_BIT_DR0         (1 << 0)

/* ADS129X SPI COMMANDS *****************************************************/

// FIXME
#define ADS129X_CMD_READ_DATA           (0x01)
#define ADS129X_CMD_READ_REGISTER       (0x10)
#define ADS129X_CMD_WRITE_REGISTER      (0x50)
#define ADS129X_CMD_SELF_OFFSET_CALIB   (0xF1)
#define ADS129X_CMD_SELF_GAIN_CALIB     (0xf2)
#define ADS129X_CMD_SYSTEM_OFFSET_CALIB (0xf3)
#define ADS129X_CMD_RESET               (0xfe)

/* SPI BUS PARAMETERS *******************************************************/

#define ADS129X_SPI_FREQUENCY   (20*1000*1000)

/* Device uses SPI Mode 1: CKPOL = 0, CKPHA = 1 */

#define ADS129X_SPI_MODE        (SPIDEV_MODE1)
/****************************************************************************
 * Public Variables
 ****************************************************************************/
struct ads1299_dev_s
{
  FAR struct spi_dev_s *spi;      /* Cached SPI device reference */
  int devno;
  const uint8_t *mux;
  uint16_t sps;
  uint8_t channel;
  uint8_t pga;
  int irq;
  FAR const struct adc_callback_s *cb;
  struct work_s work;
  bool buf;
};

extern struct adc_dev_s g_adcdev;

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* CONFIG_SPI && CONFIG_ADC_ADS129X */
#endif /* __INCLUDE_NUTTX_ANALOG_ADS129X_H */
