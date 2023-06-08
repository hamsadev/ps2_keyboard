#ifndef _PS2_KEYBOARD_H_
#define _PS2_KEYBOARD_H_

#include <stdint.h>
#include "io_define.h"
#include "StreamBuffer.h""

#define MAX_KEYBOARD_NUM    1

typedef struct {
    GPIO_TypeDef*   io;
    uint16_t        pin;
} PS2_PinConfig;

typedef uint16_t (*ReadPinFn) (PS2_PinConfig* pinConfig);
typedef void (*InitPinFn) (PS2_PinConfig* pinConfig);

typedef struct 
{
    PS2_PinConfig*   data;
    PS2_PinConfig*   clock;
}PS2_Keyboard_Channel;

typedef struct 
{
    InitPinFn initPin;
    ReadPinFn readPin;
}PS2_Keyboard_Driver;


typedef struct 
{
    PS2_Keyboard_Channel     channel;
    Stream                   stream;
    uint8_t*                 buffer;
    uint16_t                 bufferLen;
    volatile uint8_t         bitCounter;
    volatile uint8_t         makeCode;
}PS2_Keyboard_Handler;

void PS2_Keyboard_add(PS2_Keyboard_Handler* handler, uint8_t* buffer, uint16_t bufferLen);
void PS2_Keyboard_setPinConfig(PS2_Keyboard_Handler* handler, PS2_PinConfig* data, PS2_PinConfig* clock);
void PS2_Keyboard_init(void);
void PS2_Keyboard_setDriver(PS2_Keyboard_Driver* kDriver);
void PS2_Keyboard_irqHandler(PS2_Keyboard_Handler* handler);

#endif //_PS2_KEYBOARD_H_
