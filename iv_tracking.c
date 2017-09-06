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
    P1OUT ^= BIT0;
    // turn left
    if(P3IN & BIT5)
    {
        turn(LEF, V_TUR);
    }
    // turn right
    else if(P3IN & BIT6)
    {
        turn(RIT, V_TUR);
    }
    else
    {
        go_straight(V_STT);
    }
}

