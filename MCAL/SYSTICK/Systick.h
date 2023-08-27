#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "../../LIB/STD_TYPES.h"

#define SYSTEM_CLK 16000000
#define MS 1000

#define SYSTIC_ENABLE  1u<<0
#define SYSTIC_INTERRUPT_ENABLE  1u<<1
#define SYSTIC_CLK_SYSTEM  1u<<2
#define SYSTIC_CLK_PIOSC  0u<<2
#define SYSTIC_COUNT_FLAG  1U<<16

extern u8 Systick_flag;

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void);
void SysTick_Interrupt_Init(void);

// Time delay using busy wait.
// The delay parameter is in units of the core clock. (units of 12.5 nsec for 80 MHz clock)
void SysTick_Wait_ms(u32 delay);

void SysTick_Stop(void);

void SysTick_ISR_Handler(void);

#endif /* SYSTICK_H_ */
