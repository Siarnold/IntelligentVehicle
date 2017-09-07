/*
 * iv_remo_ctl.c
 *
 *  Created on: 2017Äê9ÔÂ4ÈÕ
 *      Author: ASUS
 */

#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_remo_ctl.h"

unsigned char str[3];
unsigned int flag = 0;

void remo_ctl(void)
{
    // set PIN
    P3SEL = BIT3 + BIT4;

    //
    UCA0CTL1 |= UCSWRST;
    UCA0CTL1 |= UCSSEL_1; // AClock
    UCA0BR0 = 0x03;
    UCA0BR1 = 0x00;
    UCA0MCTL = UCBRS_3 + UCBRF_0;
    UCA0CTL1 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{

    switch(__even_in_range(UCA0IV, 4))
    {
    case 0: break;
    case 2:
        // wait for sending
        // while(!(UCA0IFG&UCTXIFG));

        if(flag == 0)
        {
            str[0] = UCA0RXBUF;
            if(str[0] == 0x40)
                flag++;
            else
                flag = 0;
        }
        else if(flag == 1)
        {
            str[1] = UCA0RXBUF;
            if(str[1] == 0xBF)
                flag++;
            else
                flag = 0;
        }
        else
        {
            str[2] = UCA0RXBUF;
            flag = 0;
            switch(str[2])
            {
            case FWD:
            case BWD:
            case LWD:
            case RWD:
            case ACC:
            case VSH:
            case DSH: rc_sel = str[2]; break;
            case 0x07: mode = CCM; break;
            case 0x00: mode = BM; break;
            case 0x09: mode = RCM; break;
            default : break;
            }
        }
        // if send what is received
        //UCA0TXBUF=UCA0RXBUF;
        break;
    case 4: break;
    default: break;
    }
    LPM0_EXIT;
}
