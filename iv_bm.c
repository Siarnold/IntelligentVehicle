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

/* 0: refuse
 * 1: ready for the first ultrasonic to emit
 * 2: ready for the second ultrasonic to emit
 */
unsigned char usf_txd = 0; // usf = ultra sonic flag
/* 0: refuse
 * 1: ready for the first ultrasonic to receive
 * 2: ready for the second ultrasonic to receive
 */
unsigned char usf_rxd = 0; // usf = ultra sonic flag
unsigned char num1, num2;
unsigned int cycle1[2], cycle2[2];
unsigned int dis1, dis2;

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
    switch(usf_txd)
    {
    case 1:
        usf_txd = 0;
        usf_rxd = 1;
        P8OUT |= BIT1;
        __delay_cycles(160); // 15us
        P8OUT &= ~BIT1;
        num1 = 0; // the first cycle
        break;
    case 2:
        usf_txd = 0;
        usf_rxd = 2;
        P8OUT |= BIT2;
        __delay_cycles(160); // 15us
        P8OUT &= ~BIT2;
        num2 = 0; // the first cycle
        break;
    default: break;
    }
}


void bm_run()
{
    // first back to a proper place to use ultrasonic
    turn(RIT);
    backward();
    __delay_cycles(16000000);
    turn(STT);

    // then use ultrasonic to back at the right place
    if(flag_TA2_0 == 1)
    {
        flag_TA2_0 = 0;
        bm_ISR();
    }
}

#pragma vector = TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)
{
    unsigned int sum;

    switch(__even_in_range(TA2IV, 14))
    {
    case 0: break; // no interrupt
    case 2: // TA2CCR1
        if (usf_rxd == 1 && num1 == 0)
        {
            num1++;
            cycle1[0] = TA2CCR1;
            TA2CCTL1 = CM_2 + SCS + CAP + CCIE; // set negedge
        }
        else if (usf_rxd == 1)
        {
            usf_txd = 2;
            usf_rxd = 0;
            cycle1[1] = TA2CCR1;
            if(cycle1[1] > cycle1[0])
                sum = cycle1[1] - cycle1[0];
            else
                sum = 65536 + cycle1[1] - cycle1[0];
            dis1 = (unsigned int)(sum / 1.93);
            TA2CCTL1 = CM_1 + SCS + CAP + CCIE; // set posedge
        }
        break;
    case 4: // TA2CCR2
        if (usf_rxd == 2 && num2 == 0)
        {
            num2++;
            cycle2[0] = TA2CCR2;
            TA2CCTL2 = CM_2 + SCS + CAP + CCIE; // set negedge
        }
        else if (usf_rxd == 2)
        {
            usf_txd = 1;
            usf_rxd = 0;
            cycle2[1] = TA2CCR2;
            if (cycle2[1] > cycle2[0])
                sum = cycle2[1] - cycle2[0];
            else
                sum = 65536 + cycle2[1] - cycle2[0];
            dis2 = (unsigned int)(sum / 1.93);
            TA2CCTL2 = CM_1 + SCS + CAP + CCIE; // set posedge

            // the 2 distances are ready
            if (dis1 < DIS_WARN && dis2 < DIS_WARN)
                go_straight(0);
            else if (dis1 > dis2)
                turn(RIT);
            else
                turn(LEF);

        }
        break;
    default: break;
    }
}

