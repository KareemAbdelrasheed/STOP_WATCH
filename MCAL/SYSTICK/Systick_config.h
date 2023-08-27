/*
 * Systick_config.h
 *
 *  Created on: Aug 24, 2023
 *      Author: EUI-Support
 */

#ifndef SYSTICK_CONFIG_H_
#define SYSTICK_CONFIG_H_


#define CLK_SRC SYSTIC_CLK_SYSTEM



#if CLK_SRC == SYSTIC_CLK_SYSTEM
    /*16 MHz*/
    #define TIME_UNIT SYSTEM_CLK / MS
#endif




#endif /* SYSTICK_CONFIG_H_ */
