/**
  ******************************************************************************
  * @file     stm8s_conf.h
  * @author   MCD Application Team
  * @version  V2.0.4
  * @date     26-April-2018
  * @brief    This file is used to configure the Library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

// PlatformIO builder (for STM8 2.0.0 platform) does not propagate environment with defines from platformio.ini to determine SPL module inclusion
// all defines for module inclusion should be set/reset in main.h

#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

#include "main.h"

#include "stm8s.h"
#include "stm8s_clk.h"
//#include "stm8s_exti.h"
//#include "stm8s_flash.h"
#include "stm8s_gpio.h"
#ifdef WITH_I2C
#include "stm8s_i2c.h"
#endif
//#include "stm8s_itc.h"
//#include "stm8s_iwdg.h"
//#include "stm8s_rst.h"
//#include "stm8s_spi.h"
//#include "stm8s_tim1.h"
#include "stm8s_tim4.h"
#ifdef WITH_UART
#include "stm8s_uart1.h"
#endif
//#include "stm8s_wwdg.h"
#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */
#endif /* __STM8S_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
