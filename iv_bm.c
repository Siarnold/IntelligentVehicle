/*
 * iv_bm.c
 *
 *  Created on: 2017Äê9ÔÂ5ÈÕ
 *      Author: ASUS
 */

#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_bm.h"
#include "iv_v_meas.h"
#include "iv_temp.h"

unsigned char us_sel = 0;

void bm(void)
{
    // set the rear ultrasonics
    P8DIR |= BIT1 + BIT2;
    P8OUT &= ~(BIT1 + BIT2);
    P2DIR &= ~(BIT4 + BIT5);
    P2SEL |= BIT4 + BIT5;
    // set TA2 for catching
    TA2CTL = TASSEL_1 + MC_1 + TACLR; // ACLK + Mode of count 1
    TA2CCTL1 = CM_1 + SCS + CAP + CCIE;// pos edge + simultaneous catch + capture + Interrupt Enable
    TA2CCTL2 = CM_1 + SCS + CAP + CCIE;

    // other simultaneous functions
    v_meas();
    temp();
    set_intpt_TA2();
}

void bm_ISR(void)
{

}


void bm_run()
{
    if(flag_TA2_0 == 1)
    {
        flag_TA2_0 = 0;
        bm_ISR();
    }
}
