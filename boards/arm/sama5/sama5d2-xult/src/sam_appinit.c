/****************************************************************************
 * boards/arm/sama5/sama5d2-xult/src/sam_appinit.c
 *
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.  The
 *  ASF licenses this file to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance with the
 *  License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <syslog.h>
#include <debug.h>

#include <sam_pio.h>

#include "sama5d2-xult.h"

#include <nuttx/board.h>
#ifndef CONFIG_BUILD_KERNEL

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/*

#define LOW false
#define HIGH true

#undef PIN_LED
#undef IPIN_PWDN
#undef PIN_CLKSEL
#undef IPIN_RESET
#undef PIN_START
#undef IPIN_DRDY
#undef PIN_CS


// Arduino Due pin: D13
// SAMA5 pin: Blue: PB0
// SAMA5 pin: Green: PB5
// const int PIN_LED = 13;
#define PIN_LED_GREEN   (PIO_CFG_DEFAULT | PIO_PORT_PIOB | PIO_PIN5 | PIO_OUTPUT)
#define PIN_LED_BLUE    (PIO_CFG_DEFAULT | PIO_PORT_PIOB | PIO_PIN0 | PIO_OUTPUT)

// Arduino Due pin: D33 
// SAMA5 pin: PB28 
// const int IPIN_PWDN = 33;
#define IPIN_PWDN       (PIO_CFG_DEFAULT | PIO_PORT_PIOB | PIO_PIN28 | PIO_OUTPUT)
// Arduino Due pin: D48 
// SAMA5 pin: PC7 
// const int PIN_CLKSEL = 48;
#define PIN_CLKSEL     (PIO_CFG_DEFAULT | PIO_PORT_PIOC | PIO_PIN7 | PIO_OUTPUT) 
// Arduino Due pin: D47
// SAMA5 pin: PB12
// const int IPIN_RESET = 47;
#define IPIN_RESET     (PIO_CFG_DEFAULT | PIO_PORT_PIOB | PIO_PIN12 | PIO_OUTPUT) 

// Arduino Due pin: A5
// SAMA5 pin: PD22
// const int PIN_START = 59;
#define PIN_START      (PIO_CFG_DEFAULT | PIO_PORT_PIOD | PIO_PIN22 | PIO_OUTPUT) 
// Arduino Due pin: D24 
// SAMA5 pin: PA24 
// const int IPIN_DRDY = 24;   // board 0: JP1, pos. 1
#define IPIN_DRDY      (PIO_CFG_DEFAULT | PIO_PORT_PIOA | PIO_PIN24 | PIO_OUTPUT) 
//const int IPIN_DRDY = 25; // board 1: JP1, pos. 2
//const int IPIN_DRDY = 26; // board 2: JP1, pos. 3
//const int IPIN_DRDY = 27; // board 3: JP1, pos. 4

// Arduino Due pin: D23
// SAMA5 pin: PA14 
// const int PIN_CS = 23;   // board 0: JP2, pos. 3
#define PIN_CS         (PIO_CFG_DEFAULT | PIO_PORT_PIOA | PIO_PIN14 | PIO_OUTPUT) 

// from _sama5d2x_pinmap.h
#define PIO_SPI1_MISO_1      (PIO_PERIPHA | PIO_CFG_DEFAULT | PIO_PORT_PIOD | PIO_PIN27)
#define PIO_SPI1_MOSI_1      (PIO_PERIPHA | PIO_CFG_DEFAULT | PIO_PORT_PIOD | PIO_PIN26)
#define PIO_SPI1_SPCK_1      (PIO_PERIPHA | PIO_CFG_DEFAULT | PIO_PORT_PIOD | PIO_PIN25)

void test_gpio(void) {
  spiinfo("test_gpio: starting.");
  spiinfo("PIN_START configuration: (hex): %x\n", PIN_START);
  spiinfo("PIN_CLKSEL configuration: (hex): %x\n", PIN_CLKSEL);
  spiinfo("PIN_CS configuration: (hex): %x\n", PIN_CS);
  sam_configpio(PIN_LED_GREEN);
  sam_configpio(PIN_LED_BLUE);
  sam_configpio(PIN_START);
  sam_configpio(IPIN_PWDN);
  sam_configpio(PIN_CLKSEL);
  sam_configpio(IPIN_RESET);
  sam_configpio(PIN_CS);
  sam_piowrite(PIN_LED_BLUE, HIGH); // Blue LED off
  sam_piowrite(PIN_LED_GREEN, HIGH); // Green LED off
  sam_piowrite(PIN_LED_BLUE, LOW); // Blue LED on
  for (int i=0; i<50; i++) {
    sam_piowrite(PIN_LED_BLUE, LOW);
    usleep(100*1000);
    sam_piowrite(PIN_LED_BLUE, HIGH);
    usleep(100*1000);
  }
  while (true) {
    sam_piowrite(PIN_LED_BLUE, LOW);
    sam_piowrite(PIN_START, LOW);
    sam_piowrite(IPIN_PWDN, LOW);
    sam_piowrite(PIN_CLKSEL, LOW);
    sam_piowrite(IPIN_RESET, LOW);
    sam_piowrite(PIN_CS, LOW);
    usleep(200*1000);
    sam_piowrite(PIN_LED_BLUE, HIGH);
    sam_piowrite(PIN_START, HIGH);
    sam_piowrite(IPIN_PWDN, HIGH);
    sam_piowrite(PIN_CLKSEL, HIGH);
    sam_piowrite(IPIN_RESET, HIGH);
    sam_piowrite(PIN_CS, HIGH);
    usleep(200*1000);
  }
}
*/

/****************************************************************************
 * Name: board_ioctl
 *
 * Description:
 *   The "landing site" for much of the boardctl() interface. Generic board-
 *   control functions invoked via ioctl() get routed through here.
 *
 * Input Parameters:
 *   cmd - IOCTL command being requested.
 *   arg - Arguments for the IOCTL.
 *
 * Returned Value:
 *   we don't yet support any boardctl IOCTLs.  This function always returns
 *  -ENOTTY which is the standard IOCTL return value when a command is not
 *  supported
 *
 ****************************************************************************/

#ifdef CONFIG_BOARDCTL_IOCTL
/*
int board_ioctl(unsigned int cmd, uintptr_t arg)
{
  switch (cmd)
    {
      default:
        return -ENOTTY;
    }

  return OK;
}
*/

int board_ioctl(unsigned int cmd, uintptr_t arg)
{
  return OK;
}

/*
#if defined(CONFIG_BOARDCTL_UNIQUEID)
int board_uniqueid(uint8_t *uniqueid)
{
  if (uniqueid == NULL)
    {
      return -EINVAL;
    }

  stm32l4_get_uniqueid(uniqueid);
  return OK;
}
#endif
*/

#endif /* CONFIG_BOARDCTL_IOCTL */


/****************************************************************************
 * Name: board_app_initialize
 *
 * Description:
 *   Perform application specific initialization.  This function is never
 *   called directly from application code, but only indirectly via the
 *   (non-standard) boardctl() interface using the command BOARDIOC_INIT.
 *
 * Input Parameters:
 *   arg - The boardctl() argument is passed to the board_app_initialize()
 *         implementation without modification.  The argument has no
 *         meaning to NuttX; the meaning of the argument is a contract
 *         between the board-specific initialization logic and the
 *         matching application logic.  The value could be such things as a
 *         mode enumeration value, a set of DIP switch switch settings, a
 *         pointer to configuration data read from a file or serial FLASH,
 *         or whatever you would like to do with it.  Every implementation
 *         should accept zero/NULL as a default configuration.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned on
 *   any failure to indicate the nature of the failure.
 *
 ****************************************************************************/

int board_app_initialize(uintptr_t arg)
{
#ifndef CONFIG_BOARD_LATE_INITIALIZE
  /* Perform board initialization */

  mcinfo("Entry\n");
  return sam_bringup();
  // int ret = sam_bringup();
  // test_gpio();
  // return ret;
#else
  return OK;
#endif
}

#endif /* CONFIG_BUILD_KERNEL */
