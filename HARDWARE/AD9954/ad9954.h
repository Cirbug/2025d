#ifndef AD9954_H
#define AD9954_H

#include "main.h"

#define AD9954_REFERENCE_CLOCK_HZ 20000000UL
#define AD9954_PLL_MULTIPLIER 20U
#define AD9954_MAX_AMPLITUDE_SCALE 0x3FFFU
#define AD9954_AMPLITUDE_200MV_SCALE 6553U

uint8_t Ad9954_Init(void);
uint8_t Ad9954_SetFrequency(uint32_t frequency_hz);
uint8_t Ad9954_SetAmplitude(uint16_t amplitude_scale);
uint8_t Ad9954_SetPhase(uint16_t phase_word);
uint8_t Ad9954_SetOutput(uint32_t frequency_hz, uint16_t amplitude_scale);

#endif /* AD9954_H */
