#ifndef CABLE_GPIO_H
#define CABLE_GPIO_H

#include <stdint.h>

#define CABLE_GPIO_OUTPUT_COUNT 2U
#define CABLE_GPIO_INPUT_COUNT 4U

/* 输入位图：bit0=IN1，bit1=IN2，bit2=IN3，bit3=IN6。 */
void CableGpio_SetOutputsHighImpedance(void);
void CableGpio_EnableOutput(uint8_t index);
void CableGpio_RestoreOutputsLow(void);
uint8_t CableGpio_IsOutputHigh(uint8_t index);
uint8_t CableGpio_ReadInputMask(void);
uint8_t CableGpio_ReadShield(void);

#endif /* CABLE_GPIO_H */
