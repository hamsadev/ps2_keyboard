#include "ps2_port.h"

const PS2_Keyboard_Driver SEVEN_SEG_DRIVER = {
    ps2_initPin,
    ps2_readPin,
};

#if PS2_HW == PS2_HW_AVR
uint16_t ps2_readPin(const PS2_PinConfig* config) {     
    return config->io->InputData.Value & config->pin;     
}

void ps2_initPin(const PS2_PinConfig* config) {   
    // PullUp the pin  
    config->io->OutputData.Value |= config->pin;
}
#elif PS2_HW == PS2_HW_STM32F0  
    // TODO: Implement me later
#elif PS2_HW == PS2_HW_STM32F1  
    // TODO: Implement me later
#elif PS2_HW == PS2_HW_STM32F2
    // TODO: Implement me later
#elif PS2_HW == PS2_HW_STM32F3
    // TODO: Implement me later
#elif PS2_HW == PS2_HW_STM32F4
    // TODO: Implement me later
#else

    #error "Please select your hardware"

#endif // PS2_HW