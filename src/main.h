#ifndef __MAIN_H
#define __MAIN_H

//#define USE_FULL_ASSERT    (1) 
//#define WITH_UART 1
#define WITH_I2C 1
#define MY_I2C_ADDR 0x5Bu

extern __IO uint32_t TimingDelay;
extern __IO uint16_t keyState;
#ifdef WITH_UART
extern __IO uint32_t StatusFlags;
#endif

#endif /* __MAIN_H */