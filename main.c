#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_remo_ctl.h"
#include "iv_ccm.h"
#include "iv_bm.h"
#include "iv_rcm.h"


/**
 * main.c
 */


int main(void)
{
    unsigned char mode_curr = CCM;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	set_clock();
	set_PWM();
	remo_ctl();
	ccm();
	P1DIR |= BIT0;
	P4DIR |= BIT7;
	P1OUT &= ~BIT0;
	P4OUT &= ~BIT7;

	// __bis_SR_register(LPM0_bits + GIE);
    while(1)
    {
        __bis_SR_register(LPM0_bits + GIE);
        switch(mode)
        {
        case CCM:

            if(mode_curr != CCM)
            {
                ccm();
                ccm_run();
                mode_curr = CCM;
                P4OUT &= ~BIT7;
            }
            else
                ccm_run();
            break;
        case BM:
            if(mode_curr != BM)
            {
                bm();
                bm_run();
                mode_curr = BM;
                P4OUT |= BIT7;
                P1OUT &= ~BIT0;
            }
            else
                bm_run();
            break;
        case RCM:
            if(mode_curr != RCM)
            {
                rcm();
                rcm_run();
                mode_curr = RCM;
                P1OUT |= BIT0;
                P4OUT &= ~BIT7;
            }
            else
                rcm_run();
            break;
        default: break;
        }
    }

	return 0;
}
