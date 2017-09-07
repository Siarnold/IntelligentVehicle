/*
 * iv_basic.c
 *
 *  Created on: 2017Äê8ÔÂ30ÈÕ
 *      Author: ASUS
 */
#include <msp430f5529.h>
#include "iv_basic.h"

unsigned char mode = CCM;
unsigned char flag_TA2_0 = 0;
unsigned char sel = 0;
unsigned char rc_sel = FWD;
unsigned char vt_sel = D_SH;

void set_PWM(void)
{
    // set pin for PWM
    P1DIR |= BIT2 + BIT4 + BIT5; // 1.2 steer, 1.4 motor PWM OUT
    P1SEL |= BIT2 + BIT4 + BIT5; // internal CLOCK

    // PWM duty ratio = DR
    // 300Hz DR 63-64% straight 109*63%=69
    // 72% left turning sup     109*71%=77
    // 57% right turning sup    109*57%=63
    TA0CCR0 = 109; // count sup
    TA0CCTL1 = OUTMOD_7;
    TA0CCR1 = STT;
    TA0CTL = TASSEL_1 + MC_1 + TACLR;
    TA0CCTL3 = OUTMOD_7;
    TA0CCR3 = 0; // duty ratio 0/109 for motor
    TA0CCTL4 = OUTMOD_7; // the backing mode
    TA0CCR4 = 0;
}

void set_clock(void)
{
    //set clock
    //AClock = 32kHz, MClock = SMClock = 8MHz
    UCSCTL3 = SELREF_2;
    UCSCTL4 |= SELA_2;
    UCSCTL0 = 0x0000;
    do
    {
    UCSCTL7 &= ~(XT2OFFG+XT1LFOFFG+DCOFFG);
    SFRIFG1 &= ~OFIFG;
    } while(SFRIFG1&OFIFG);
    __bis_SR_register(SCG0);
    UCSCTL1 = DCORSEL_5;
    //UCSCTL2 |= 31; // 1048576
    UCSCTL2 |= 249; // 8M
    __bic_SR_register(SCG0);
    __delay_cycles(250000);
}

void set_intpt_TA2(void)
{
    TA2CTL = TASSEL_1 + MC_1 + TACLR;
    TA2CCR0 = 1600; // count sup
    TA2CCTL0 = CCIE;
}

// interrupt by main clock A2
#pragma vector = TIMER2_A0_VECTOR
__interrupt void  TIMER2_A0_ISR(void)
{
    flag_TA2_0 = 1;
    LPM0_EXIT;
}

