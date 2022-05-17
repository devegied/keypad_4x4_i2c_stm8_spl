
/**
  ******************************************************************************
  * @file     stm8s_it.h
  * @author   MCD Application Team
  * @version  V2.0.4
  * @date     26-April-2018
  * @brief    This file contains the headers of the interrupt handlers
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
#ifndef __STM8S_IT_H
#define __STM8S_IT_H
#include "stm8s.h"

INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler);                 /* TRAP */
INTERRUPT_HANDLER(TLI_IRQHandler, 0);                    /* TLI */
INTERRUPT_HANDLER(AWU_IRQHandler, 1);                    /* AWU */
INTERRUPT_HANDLER(CLK_IRQHandler, 2);                    /* CLOCK */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3);             /* EXTI PORTA */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4);             /* EXTI PORTB */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5);             /* EXTI PORTC */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6);             /* EXTI PORTD */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7);             /* EXTI PORTE */
INTERRUPT_HANDLER(SPI_IRQHandler, 10);                   /* SPI */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11);  /* TIM1 UPD/OVF/TRG/BRK */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12);          /* TIM1 CAP/COM */
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13);      /* TIM2 UPD/OVF/BRK */
INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14);          /* TIM2 CAP/COM */
INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17);              /* UART1 TX */
INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18);              /* UART1 RX */
INTERRUPT_HANDLER(I2C_IRQHandler, 19);                   /* I2C */
INTERRUPT_HANDLER(ADC1_IRQHandler, 22);                  /* ADC1 */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23);          /* TIM4 UPD/OVF */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24);            /* EEPROM ECC CORRECTION */
#endif /* __STM8S_IT_H */