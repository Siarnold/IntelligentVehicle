/*
 * iv_temp.c
 *
 *  Created on: 2017Äê9ÔÂ5ÈÕ
 *      Author: ASUS
 */

#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_temp.h"
#include "iv_digit.h"

void temp(void)
{
    ADC12CTL0 = ADC12SHT02 + ADC12ON;
    ADC12CTL1 = ADC12SHP;
    ADC12IE = BIT0;
    ADC12CTL0 |= ADC12ENC;

    // set pin
    P6SEL |= BIT0;   //p6.0, ADC in

    // set buzzer
    set_buzzer();
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    unsigned int tmp;
    if (__even_in_range(ADC12IV, 34) == 6) //ADC12IFG0
        tmp = ADC12MEM0;
    else
        tmp = 0;

    if (tmp < 4095 && tmp > 0)
        n_display(tmp);

//    if(vt_sel == T_SH)
//    {
//        if(tmp >= 0XFFF)
//        {
//            digit_display(0,0,3,0);
//            beep();
//        }
//        else
//        {
//            mute();
//            if(tmp >= 3574)
//                digit_display(0,0,4,0);
//            else if(tmp >= 2437)
//                digit_display(0,0,5,0);
//            else if(tmp >= 1874)
//                digit_display(0,0,6,0);
//            else if(tmp >= 1067)
//                digit_display(0,0,7,0);
//            else if(tmp > 0)
//                digit_display(0,0,8,0);
//            else
//                digit_display(0,0,0,0);
//        }
//    }
}


