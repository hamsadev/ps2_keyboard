/**
 * @file seven_seg_port.h
 * @author Hamid Salehi (hamsame.dev@gmail.com)
 * @brief this file show how to port lib into new hardware
 *          and have multiple of pre-implemented ports
 * @date 2023-06-08
 * 
 * @copyright Copyright (c) 2021 Hamid_Salehi
 * 
 */

#ifndef _SEVEN_SEG_PORT_H_
#define _SEVEN_SEG_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ps2_keyboard.h"
#include "io_define.h"

extern const PS2_Keyboard_Driver SEVEN_SEG_DRIVER;

void ps2_initPin(const PS2_PinConfig* config);
uint16_t ps2_readPin(const PS2_PinConfig* config);

#ifdef __cplusplus
};
#endif

#endif /* _SEVEN_SEG_PORT_H_ */