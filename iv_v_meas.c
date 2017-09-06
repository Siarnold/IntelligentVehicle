/*
 * iv_v_meas.c
 *
 *  Created on: 2017年9月3日
 *      Author: ASUS
 */

#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_digit.h"
#include "iv_v_meas.h"


unsigned int last_counter = 0;

void v_meas(void)
{
    // set pin for hall
    P7DIR &= ~BIT4 ; // P7.4 IN
    P7SEL |= BIT4;
    TBCTL = TBSSEL_1 + MC_2 + TBCLR;   //TBSSEL_1 = ACLK,   MC_2=连续计数模式,   TBCLR=清除TAR
    TBCCTL2 = CM_1 + SCS + CAP + CCIE;   //TBCCR1上升沿捕获，同步捕获，捕获模式，中断使能
}

#pragma vector = TIMERB1_VECTOR
__interrupt void  TIMERB1_ISR(void)
{
    unsigned int current_counter;
    unsigned int dif_counter;
    unsigned int frq, i;
    unsigned int d[4];

    current_counter = TBCCR2;
    if(current_counter > last_counter) dif_counter = current_counter - last_counter;
    else dif_counter = 65536 + current_counter - last_counter;
    last_counter = current_counter;
    frq = 32768 / dif_counter;


    for(i = 0; i < 4; i++)
    {
        d[i] = frq % 10;
        frq /= 10;
    }

    if(vt_sel == V_SH && d[3] == 0)
        digit_display(d[3], d[2], d[1], d[0]);

}



