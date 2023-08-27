#include "Systick.h"
#include "Systick_config.h"

/*Initialize SysTick with busy wait running at bus clock.*/
#define NVIC_ST_CTRL_R          (*((volatile u32 *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile u32 *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile u32 *)0xE000E018))

extern u8 time;

u8 Systick_flag = 0;
void SysTick_Init(void){

    /* disable SysTick during setup*/
    NVIC_ST_CTRL_R =  0;

    /* enable SysTick with core clock and clock*/
    NVIC_ST_CTRL_R |= (SYSTIC_ENABLE | CLK_SRC | SYSTIC_INTERRUPT_ENABLE |SYSTIC_CLK_SYSTEM) ;

}

/* The delay parameter is in units of the 16 MHz core clock. (62.5 ns)*/
void SysTick_Wait_ms(u32 delay){

    delay *= (TIME_UNIT);

    /*number of counts to wait*/
    NVIC_ST_RELOAD_R = delay-1;
    /*any value written to CURRENT clears*/
    NVIC_ST_CURRENT_R = 0;
}

void SysTick_Stop(void)
{
    NVIC_ST_CTRL_R &= ~(SYSTIC_ENABLE);
}

void SysTick_ISR_Handler(void)
{
    Systick_flag =1 ;
}




