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

#include <nuttx/board.h>

#include "sama5d2-xult.h"

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

#define PIN_LED         (GPIO_PORT_PIOB | GPIO_PIN27 | GPIO_OUTPUT)
#define IPIN_PWDN       (GPIO_PORT_PIOC | GPIO_PIN1 | GPIO_OUTPUT)
#define PIN_CLKSEL      (GPIO_PORT_PIOC | GPIO_PIN15 | GPIO_OUTPUT)
#define IPIN_RESET      (GPIO_PORT_PIOC | GPIO_PIN16 | GPIO_OUTPUT)
#define PIN_START       (GPIO_PORT_PIOA | GPIO_PIN4 | GPIO_OUTPUT)
#define IPIN_DRDY       (GPIO_PORT_PIOA | GPIO_PIN15 | GPIO_OUTPUT)
#define PIN_CS          (GPIO_PORT_PIOA | GPIO_PIN14 | GPIO_OUTPUT)

void test_gpio(void) {
  spiinfo("test_gpio: starting.");
  spiinfo("PIN_START configuration: (hex): %x\n", PIN_START);
  spiinfo("PIN_CLKSEL configuration: (hex): %x\n", PIN_CLKSEL);
  spiinfo("PIN_CS configuration: (hex): %x\n", PIN_CS);
  sam_configgpio(PIN_LED);
  sam_configgpio(PIN_START);
  sam_configgpio(IPIN_PWDN);
  sam_configgpio(PIN_CLKSEL);
  sam_configgpio(IPIN_RESET);
  sam_configgpio(PIN_CS);
  while (true) {
    sam_gpiowrite(PIN_LED, LOW);
    sam_gpiowrite(PIN_START, LOW);
    sam_gpiowrite(IPIN_PWDN, LOW);
    sam_gpiowrite(PIN_CLKSEL, LOW);
    sam_gpiowrite(IPIN_RESET, LOW);
    sam_gpiowrite(PIN_CS, LOW);
    usleep(200*1000);
    sam_gpiowrite(PIN_LED, HIGH);
    sam_gpiowrite(PIN_START, HIGH);
    sam_gpiowrite(IPIN_PWDN, HIGH);
    sam_gpiowrite(PIN_CLKSEL, HIGH);
    sam_gpiowrite(IPIN_RESET, HIGH);
    sam_gpiowrite(PIN_CS, HIGH);
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
#else
  return OK;
#endif
}

#endif /* CONFIG_BUILD_KERNEL */
