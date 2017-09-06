/*
 * iv_ccm.c
 *
 *  Created on: 2017Äê9ÔÂ5ÈÕ
 *      Author: ASUS
 */

#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_ccm.h"
#include "iv_tracking.h"
#include "iv_ob_avoid.h"
#include "iv_v_meas.h"
#include "iv_temp.h"

void ccm(void)
{
    tracking();
    ob_avoid();
    v_meas();
    temp();
    set_intpt_TA2();
}

void ccm_run(void)
{
    if(mode != RCM)
    {
        if(flag_TA2_0 == 1)
        {

            flag_TA2_0 = 0;
            sel++;
            switch(sel)
            {
            case TRAC: tracking_ISR(); break;
            case OBAV: ob_avoid_ISR(); break;
            case TEMP: adc_start(); sel = 0; break;
            default: break;
            }
        }
    }
    else
        adc_start();
}
