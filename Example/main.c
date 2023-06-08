#include <delay.h>
#include <alcd.h>
#include <stdio.h>

#include "ps2_keyboard.h"
#include "ps2_port.h"
#include "StreamBuffer.h"

#define LCD_MAX_CHAR    32

static const PS2_PinConfig data = {
    GPIOD, GPIO_PIN_3
};
static const PS2_PinConfig clock = {
    GPIOD, GPIO_PIN_3
};
static PS2_Keyboard_Handler keyboard;
static uint8_t buffer[64];

void extIntrruptInit(void);

void main (void)
{
    char lcd_buffer[16];
    uint8_t lcdContentLen = 0; 
       
    
    // You MUST set the driver first     
    PS2_Keyboard_setDriver(&SEVEN_SEG_DRIVER);
    PS2_Keyboard_add(&keyboard, buffer, sizeof(buffer));
    PS2_Keyboard_setPinConfig(&keyboard, &data, &clock);
    PS2_Keyboard_init();
                  
    // Init external interrupt
    extIntrruptInit();   
               
    // Init ALCD
    lcd_init(16); 
    lcd_clear();
    lcd_gotoxy(0,0);
               
    // Enable global interrput
    #asm("sei")

    while (1)
    {    
        uint16_t dataLen = Stream_available(&keyboard.stream);
        if(dataLen > 0)
        {           
            while(dataLen-- > 0)
            {
                uint8_t ch = Stream_readChar(&keyboard.stream);
                sprintf(lcd_buffer, "%02X", ch);
                lcdContentLen += 2;
                if(lcdContentLen > LCD_MAX_CHAR)
                {                  
                    // Clear lcd if is full   
                    lcd_clear();
                    lcd_gotoxy(0,0);
                    lcdContentLen = 0;    
                }
                lcd_puts(lcd_buffer);  
            }   
        }   
    }    
}

void extIntrruptInit(void)
{
    GICR|=(0<<INT1) | (1<<INT0) | (0<<INT2);
    MCUCR=(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);
    GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);
}

interrupt[EXT_INT0] void keyboardHandlerIRQ(void)
{
    PS2_Keyboard_irqHandler(&keyboard);
}