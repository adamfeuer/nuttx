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

/****************************************************************************
 * Public Types
 ****************************************************************************/



/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 *
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
 
static void adc_lock(FAR struct spi_dev_s *spi);
static void adc_unlock(FAR struct spi_dev_s *spi);
static int adc_bind(FAR struct adc_dev_s *dev,
                    FAR const struct adc_callback_s *callback);
static void adc_reset(FAR struct adc_dev_s *dev);
static int adc_setup(FAR struct adc_dev_s *dev);
static void adc_shutdown(FAR struct adc_dev_s *dev);
static void adc_rxint(FAR struct adc_dev_s *dev, bool enable);
static int adc_ioctl(FAR struct adc_dev_s *dev, int cmd, unsigned long arg);
static void adc_worker(FAR void *arg);
static int adc_interrupt(int irq, void *context, FAR void *arg);
FAR struct adc_dev_s *up_ads1299initialize(FAR struct spi_dev_s *spi,
                                           unsigned int devno);
FAR struct adc_dev_s *get_ads1299(void); 


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* CONFIG_SPI && CONFIG_ADC_ADS129X */
#endif /* __INCLUDE_NUTTX_ANALOG_ADS129X_H */
