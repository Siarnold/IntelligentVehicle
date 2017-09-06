/*
 * iv_tracking.c
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: ASUS
 */
#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_tracking.h"

void tracking(void)
{
    // set pin for infrared
    P3DIR &= ~(BIT5 + BIT6); // P3.5, 3.6 IN
}

void tracking_ISR(void)
{
    unsigned char lb, rb; // left black, right black
    P1OUT ^= BIT0;

    lb = P3IN & BIT5;
    rb = P3IN & BIT6;

    if(lb && rb)
        go_straight(0);
    else if(lb)
        go_turn(LEF, V_TUR);
    else if(rb)
        go_turn(RIT, V_TUR);
    else
        go_straight(V_STT);
}

