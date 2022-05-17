/**
  ******************************************************************************
  * @file     stm8s_it.c
  * @author   MCD Application Team
  * @version  V2.0.4
  * @date     26-April-2018
  * @brief    Main Interrupt Service Routines.
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
#include "stm8s_it.h"
#include "main.h"

__IO uint16_t Event = 0x00;
#ifdef WITH_UART
__IO uint32_t StatusFlags = 0x00;
#endif

//@brief  I2C Interrupt routine
INTERRUPT_HANDLER(I2C_IRQHandler, 19){
  // Read SR2 register to check for I2C error
  if (((I2C->SR2)&(~I2C_SR2_AF)) != 0){// Leave I2C_SR2_AF (Acknowledge Failure) for further processing
    //I2C_SR2_WUFH Wake-up from Halt
    //I2C_SR2_OVR  Overrun/Underrun
    //I2C_SR2_ARLO Arbitration Lost (master mode)
    //I2C_SR2_BERR Bus Error
#ifdef WITH_UART
    StatusFlags = (StatusFlags & 0xFFFFFF00)|I2C->SR2;
#endif
    I2C->CR2 |= I2C_CR2_STOP;  // stop communication - release the lines
    I2C->SR2 = 0;// Clear error in SR2 register
  }
  Event = I2C_GetLastEvent();
#ifdef WITH_UART
  StatusFlags = (StatusFlags & 0x0000FFFF)|((uint32_t)Event << 16);
#endif
  switch (Event)
  {
    // ******* Slave transmitter ******
    case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED://0x0682: TRA, BUSY, TXE and ADDR flags
      I2C_SendData(BYTE_0(keyState));//lower byte
      break;
    case I2C_EVENT_SLAVE_BYTE_TRANSMITTING://0x0680: TRA, BUSY and TXE flags
      I2C_SendData(BYTE_1(keyState));//higher byte
      break;
    case I2C_EVENT_SLAVE_BYTE_TRANSMITTED://TRA, BUSY, TXE and BTF flags
      I2C_SendData(BYTE_1(keyState));//higher byte
      break;
    case I2C_EVENT_SLAVE_ACK_FAILURE://0x0004: AF flag - master does not want more data
      I2C->SR2 &= ~I2C_SR2_AF;// clear AF
      break;
    // ******* Slave receiver *******
    case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED://0x0202: BUSY and ADDR flags
      break;
    case I2C_EVENT_SLAVE_BYTE_RECEIVED://0x0240: BUSY and RXNE flags
      I2C_ReceiveData();//discard received byte
      break;
    case (I2C_EVENT_SLAVE_STOP_DETECTED)://0x0010: STOPF flag
      I2C->CR2 |= I2C_CR2_ACK;// write to CR2 to clear STOPF flag
      break;
    default:
      break;
  }
}
//@brief  Timer4 Update/Overflow Interrupt routine
 INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
  if (TimingDelay != 0x00U)
    TimingDelay--;
  TIM4_ClearITPendingBit(TIM4_IT_UPDATE);//Cleat Interrupt Pending bit
}

//all other empty handlers
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler){}
INTERRUPT_HANDLER(TLI_IRQHandler, 0){}
INTERRUPT_HANDLER(AWU_IRQHandler, 1){}
INTERRUPT_HANDLER(CLK_IRQHandler, 2){}
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3){}
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4){}
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5){}
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6){}
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7){}
INTERRUPT_HANDLER(SPI_IRQHandler, 10){}
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11){}
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12){}
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13){}
INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14){}
INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17){}
INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18){}
INTERRUPT_HANDLER(ADC1_IRQHandler, 22){}
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24){}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/