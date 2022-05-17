## STM8 as I2C matrix keyboard controler

Firmware for STM8 to act as matrix keyboard controler with I2C interface

- Only simplest reporting over I2C implemented (current state of matrix keys)
- Key states are scaned periodicaly and some state change buffering can be implemented
- Uses Standard Peripheral Library for STM8S
- I2C slave interface imlemented with interrupts
- Uses SDCC
- PlatformIO project provided

I use it with [4x4 Matrix Keypad](https://www.adafruit.com/product/3844) and [STM8S103F3 Breakout Board](https://www.aliexpress.com/wholesale?SearchText=STM8S103F3P6+system+board)

## Inspiration

- Standard Peripheral Library Examples
- [First steps for the Keyboard controller](https://hackaday.io/project/27520-pimp-personal-information-manager-pager/log/129973-first-steps-for-the-keyboard-controller)

## License

Parts of code under [MCD-ST Liberty SW License Agreement V2](http://www.st.com/software_license_agreement_liberty_v2)

Copyright (c) 2022, devegied

Copyright (c) 2014, STMicroelectronics