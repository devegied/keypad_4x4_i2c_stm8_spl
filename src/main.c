
/**
  ******************************************************************************
  * @file UART1_Printf\main.c
  * @file I2C/I2C_TwoBoards/I2C_DataExchange/Slave/main.c
  * @brief This file contains the main function for: retarget the C library printf/scanf functions to the UART1 example.
  * @author  MCD Application Team
  * @version V2.0.4
  * @date     26-April-2018
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
#include "stm8s.h"
#include "stm8s_it.h"
#include "main.h"

#ifdef WITH_UART
#include "stdio.h"
#endif

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? ((value) |= (1UL << (bit))) : ((value) &= ~(1UL << (bit))))
/* KB Matrix connections
  + - + - + - + - PC6
  |   |   |   |
  + - + - + - + - PC5
  |   |   |   |
  + - + - + - + - PC4
  |   |   |   |
  + - + - + - + - PC3
  |   |   |   |
 PD3 PD2 PD1 PC7
 */
#define rowsPort GPIOC
const uint8_t rows[] = {GPIO_PIN_6,GPIO_PIN_5,GPIO_PIN_4,GPIO_PIN_3};
#define rowCount 4
GPIO_TypeDef *colsPorts[] = {GPIOD,GPIOD,GPIOD,GPIOC};
const uint8_t cols[] = {GPIO_PIN_3,GPIO_PIN_2,GPIO_PIN_1,GPIO_PIN_7};
#define colCount 4

uint8_t counter=0;
uint16_t keyStateLast=0;
__IO uint16_t keyState=0;
__IO uint32_t TimingDelay = 0;
void Delay(__IO uint32_t nTime/*in milliseconds*/)
{
  TimingDelay = nTime;
  while (TimingDelay > 0x00U)//decremented in TIM4 interrupt every 1 ms
    wfi();  // Puts the processor in wait mode until an interrupt is received.
}
void readMatrix() {
  for (uint8_t colIndex=0; colIndex < colCount; colIndex++) {
    GPIO_Init(colsPorts[colIndex], cols[colIndex], GPIO_MODE_OUT_PP_LOW_FAST);
    for (uint8_t rowIndex=0; rowIndex < rowCount; rowIndex++) {
      uint8_t rowCol = rows[rowIndex],keyIndex=(rowIndex<<2)+colIndex;
      BitStatus lastPressed = bitRead(keyStateLast,keyIndex),currPressed;
      GPIO_ExternalPullUpConfig(rowsPort, rows[rowIndex],ENABLE);//GPIO_Init(rowsPort, rows[rowIndex], GPIO_MODE_IN_PU_NO_IT);
      Delay(1);
      currPressed = !GPIO_ReadInputPin(rowsPort, rows[rowIndex]);// 0 for pressed - invert it
      if(lastPressed==currPressed)
        bitWrite(keyState,keyIndex,currPressed);
      bitWrite(keyStateLast,keyIndex,currPressed);
      GPIO_ExternalPullUpConfig(rowsPort, rows[rowIndex],DISABLE);//GPIO_Init(rowsPort, rows[rowIndex], GPIO_MODE_IN_FL_NO_IT);
    }
    GPIO_Init(colsPorts[colIndex], cols[colIndex], GPIO_MODE_IN_FL_NO_IT);
  }
}
void main(void){
  /*High speed internal clock prescaler: 1*/
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
#ifdef WITH_I2C
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);
#else
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
#endif
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
#ifdef WITH_UART
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, ENABLE);
#else
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);
#endif
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);

#ifdef WITH_I2C
  /* Configure I2C */
  I2C_DeInit();
  GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);//SCL
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_IN_PU_NO_IT);//SDA
  I2C_Cmd(ENABLE);
  I2C_Init(I2C_MAX_FAST_FREQ/*400kHz*/, MY_I2C_ADDR<<1, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);
  /* Enable I2C Interrupts*/
  I2C_ITConfig((I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
#else
  /* Initialize I/Os for LED on PB5, initialy no pull to ground */
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_SLOW);
#endif

  /* Configure TIM4 */
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_128,124);/*1ms*/
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);
  TIM4_Cmd(ENABLE);

#ifdef WITH_UART 
  /* Configure UART1 */
  UART1_DeInit();
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TX_ENABLE);
#endif

  /* Configure keypad I/O */
  for(counter = 0; counter < rowCount; counter++)
    GPIO_Init(rowsPort, rows[counter], GPIO_MODE_IN_FL_NO_IT);
  for(counter = 0; counter < colCount; counter++)
    GPIO_Init(colsPorts[counter], cols[counter], GPIO_MODE_IN_FL_NO_IT);
  
  /* Enable general interrupts */
  enableInterrupts();
#ifdef WITH_UART 
  /* Output a message on serial using printf function */
  printf("\nUART1\n");
#endif
  while (1)
  {
    counter=100;
    while(counter--){
      readMatrix();
      Delay(10);
    }
#ifdef WITH_UART
    printf("0x%06lx 0x%04x 0x%04x\n", StatusFlags, keyState, keyStateLast);
#endif
#ifndef WITH_I2C
    GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
#endif
  }
}

#ifdef WITH_UART 
int putchar(int c){//Retargets the C library printf function to the UART.
  UART1_SendData8(c);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
  return (c);
}
#endif
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){ 
  (void) file;
  (void) line;
  while (1){}
}
#endif