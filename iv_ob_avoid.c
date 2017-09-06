/*
 * iv_ob_avoid.c
 *
 *  Created on: 2017年8月31日
 *      Author: ASUS
 */

#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_ob_avoid.h"

unsigned int num = 0;
unsigned int cycle[2];

void ob_avoid(void)
{
    // set pin for ultrasound
    P2DIR |= BIT2; // P2.2 OUT
    P2OUT &= ~BIT2;
    P2DIR &= ~BIT0; // P2.0 IN
    P2SEL |= BIT0; // peripheral function: TA1CCR1

    // set TA1 for catching
    TA1CTL = TASSEL_2 + MC_2 + TACLR; // TASSEL_2=SMCLK, MC_2=连续计数模式, TACLR=清除TAR
    TA1CCTL1 = CM_1 + SCS + CAP + CCIE; // TA1CCR1上升沿捕获，同步捕获，捕获模式，Interrupt Enable
    TA1CCTL2 = CM_1 + SCS + CAP + CCIE;
}


void ob_avoid_ISR(void)
{
    P2OUT |= BIT2;
    __delay_cycles(160); // 15us
    P2OUT &= ~BIT2;
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)
{
    unsigned int sum;
    float dis = 2 * DIS_WARN;

    switch(__even_in_range(TA1IV, 14))
    {
    case 0: break; // no interrupt
    case 2: // TA1CCR1
        if(num == 0)
        {
            num++;
            cycle[0] = TA1CCR1; // store the count result
            TA1CCTL1 = CM_2 + SCS + CAP + CCIE; // TA1CCR1 neg-edge catch
            dis = 2 * DIS_WARN;
        }
        else
        {
            cycle[1] = TA1CCR1; // store the count result
            if(cycle[1] > cycle[0])
                sum = cycle[1] - cycle[0];
            else
                sum = 65536 + cycle[1] - cycle[0];
            dis = (1.0 / 480) * sum; // dis1tance unit: cm
            num = 0;
            TA1CCTL1 = CM_1 + SCS + CAP + CCIE;   //TA1CCR1上升沿捕获，同步捕获，捕获模式，中断使能
        }
        break;
    default: break;
    }

    // avoidance strategy
    if(dis < DIS_WARN)
    {
        turn(RIT, V_TUR);
        sel = TRAC; // set the priority of ob_avoid higher than tracking
    }
    // if the distance is safe, the tracking model will take control
}


