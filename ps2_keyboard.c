#include "ps2_keyboard.h"
#include <string.h>

#ifndef NULL
    #define NULL    (void*)0
#endif //NULL

#define MAKE_CODE_FRAME_BIT_NUM     11

static PS2_Keyboard_Driver* driver;
static PS2_Keyboard_Handler* keyboard[MAX_KEYBOARD_NUM];
static uint16_t keyboardLen = 0;

void PS2_Keyboard_add(PS2_Keyboard_Handler* handler, uint8_t* buffer, uint16_t bufferLen)
{
    keyboard[keyboardLen] = handler;
    handler->bitCounter = MAKE_CODE_FRAME_BIT_NUM;
    handler->buffer = buffer;
    handler->bufferLen = bufferLen;
    keyboardLen++;
}

void PS2_Keyboard_setPinConfig(PS2_Keyboard_Handler* handler, PS2_PinConfig* data, PS2_PinConfig* clock)
{
    handler->channel.data = data;
    handler->channel.clock = clock;  
    
    driver->initPin(data);
    driver->initPin(clock);     
}

void PS2_Keyboard_init(void)
{   
    uint8_t i;
    for (i = 0; i < keyboardLen; i++)
    {      
        memset(keyboard[i]->buffer, 0, keyboard[i]->bufferLen);
        Stream_init(&keyboard[i]->stream, keyboard[i]->buffer, keyboard[i]->bufferLen);
    }
}

void PS2_Keyboard_setDriver(PS2_Keyboard_Driver* kDriver)
{
    driver = kDriver;
}

void PS2_Keyboard_irqHandler(PS2_Keyboard_Handler* handler)
{    
    if(handler->bitCounter < 11 && handler->bitCounter > 2)
    {
        handler->makeCode >>= 1;
        if(driver->readPin(handler->channel.data))
        {
            handler->makeCode |= 0x80;
        }
    }
    // TODO: Add parity check on 10th bit

    if(--handler->bitCounter == 0)
    {
        handler->bitCounter = MAKE_CODE_FRAME_BIT_NUM;         
        Stream_writeChar(&handler->stream, handler->makeCode);
    }
}


