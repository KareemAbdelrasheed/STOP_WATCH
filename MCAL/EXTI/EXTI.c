#include "../../LIB/STD_TYPES.h"
#include "../../LIB/tm4c123gh6pm.h"

#include "EXTI.h"

extern u8 FLAG_SWITCH;

void delayMs(u32 n);

void ISR_SWITCH(void)
{
    delayMs(40);
    FLAG_SWITCH = GPIO_PORTF_RIS_R;

    GPIO_PORTF_ICR_R=0xFF;
}

void ISR_SWITCH_INIT(void)
{
    /*Enable PORTA Interrupt */
    NVIC_EN0_R |= (1<<30);

    /*Enable mask interrupt for selected pins */
    GPIO_PORTF_IM_R |= 0x11;
}

