/**
 * @file io_define.h
 * @author Hamid Salehi (hamsame.dev@gmail.com.com)
 * @brief set mcu hardware
 * @version 0.1
 * @date 2023-06-08
 */
#ifndef _IO_DEFINE_H_
#define _IO_DEFINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define PS2_HW_AVR          1
#define PS2_HW_STM32F0      2
#define PS2_HW_STM32F1      3
#define PS2_HW_STM32F2      4
#define PS2_HW_STM32F3      5
#define PS2_HW_STM32F4      6

/**
 * @brief set your hardware from above list
 */
#ifndef PS2_HW
    #define PS2_HW              PS2_HW_AVR
#endif

#if PS2_HW == PS2_HW_AVR
typedef union {
  uint8_t       Value;  
  struct {
      uint8_t   Bit0    : 1;
      uint8_t   Bit1    : 1;
      uint8_t   Bit2    : 1;
      uint8_t   Bit3    : 1;
      uint8_t   Bit4    : 1;
      uint8_t   Bit5    : 1;
      uint8_t   Bit6    : 1;
      uint8_t   Bit7    : 1;
  };
} GPIO_Register;
/**
 * @brief compact 3 io register into one struct
 */
typedef struct {
    // PIN
    volatile GPIO_Register InputData;
    // DDR
    volatile GPIO_Register Direction;
    // PORT
    volatile GPIO_Register OutputData;
} GPIO_TypeDef;

#define GPIOA           ((GPIO_TypeDef*) 0x39)
#define GPIOB           ((GPIO_TypeDef*) 0x36)
#define GPIOC           ((GPIO_TypeDef*) 0x33)
#define GPIOD           ((GPIO_TypeDef*) 0x30)

#define GPIO_PIN_0      0x01
#define GPIO_PIN_1      0x02
#define GPIO_PIN_2      0x04
#define GPIO_PIN_3      0x08
#define GPIO_PIN_4      0x10
#define GPIO_PIN_5      0x20
#define GPIO_PIN_6      0x40
#define GPIO_PIN_7      0x80

/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */
typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
}GPIO_PinState;

#elif PS2_HW == PS2_HW_STM32F0 
    #include "stm32f0xx.h"
#elif PS2_HW == PS2_HW_STM32F1 
    #include "stm32f1xx.h"
#elif PS2_HW == PS2_HW_STM32F2
    #include "stm32f2xx.h"
#elif PS2_HW == PS2_HW_STM32F3
    #include "stm32f3xx.h"
#elif PS2_HW == PS2_HW_STM32F4
    #include "stm32f4xx.h"
#else
    #error "Please select your hardware"
#endif
#ifdef __cplusplus
};
#endif

#endif /* _IO_DEFINE_H_ */
