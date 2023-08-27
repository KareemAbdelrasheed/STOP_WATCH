#include "../MCAL/SYSTICK/Systick.h"

#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/GPIO/GPIO_private.h"
#include "../MCAL/EXTI/EXTI.h"

#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KEYPAD/keypad_interface.h"


#define MILISECONDS 10
#define SECONDS 60
#define MINUTE 600

extern u8 Systick_flag;

u8 FLAG_SWITCH;
u32 time =0;

u32 Flag_pause=1;
u8 Flag_reset=0;
u32 minuts=0;
u32 seconds=0;
u32 melliseconds=0;

void APP_SysSetup(void)
{
    SysTick_Init();

    LCD_voidInit();

    GPIO_voidInit(GPIO_PORTF);
    GPIO_voidInput(GPIO_PORTF ,GPIO_PF0, PULL_UP);
    GPIO_voidInput(GPIO_PORTF ,GPIO_PF4, PULL_UP);

    ISR_SWITCH_INIT();

    SysTick_Wait_ms(1000);
}

void APP_SysOn(void)
{
    if(FLAG_SWITCH== 1)
    {
        Flag_pause ^= 1;

        if( Flag_pause==0)
        {
            LCD_voidGoToXY(1,0);
            LCD_voidSendString("PAUSED  ");
            LCD_voidSendNumber(minuts);
            LCD_voidSendData(':');
            LCD_voidSendNumber(seconds);
            LCD_voidSendData('.');
            LCD_NoLeadingZerosVoidSendNumber(melliseconds);

        }
        else
        {
            if(Flag_reset==0)
            {
                LCD_voidGoToXY(1,0);
                LCD_voidSendString("        ");
                LCD_voidSendNumber(minuts);
                LCD_voidSendData(':');
                LCD_voidSendNumber(seconds);
                LCD_voidSendData('.');
                LCD_NoLeadingZerosVoidSendNumber(melliseconds);
            }

        }
        FLAG_SWITCH=0;
    }
    else if(FLAG_SWITCH== 0x10)
    {
        time=0;
        melliseconds=0;
        seconds=0;
        minuts=0;
        FLAG_SWITCH=0;
        LCD_voidSendCommand(0x1);
        LCD_voidGoToXY(0,0);
        LCD_voidSendNumber(minuts);
        LCD_voidSendData(':');
        LCD_voidSendNumber(seconds);
        LCD_voidSendData('.');
        LCD_NoLeadingZerosVoidSendNumber(melliseconds);
        SysTick_Wait_ms(100);

    }
    if(Systick_flag==1 && Flag_pause==1)
    {
        Flag_reset=0;
        SysTick_Wait_ms(100);
        time ++;
        melliseconds = time%MILISECONDS;
        seconds = (time / MILISECONDS)%60;
        minuts = (time / MINUTE)%60;


        LCD_voidGoToXY(0,0);
        LCD_voidSendNumber(minuts);
        LCD_voidSendData(':');
        LCD_voidSendNumber(seconds);
        LCD_voidSendData('.');
        LCD_NoLeadingZerosVoidSendNumber(melliseconds);

        Systick_flag = 0;
    }

}
