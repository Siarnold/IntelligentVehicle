/*
 * iv_rcm.c
 *
 *  Created on: 2017Äê9ÔÂ6ÈÕ
 *      Author: ASUS
 */

#include <msp430f5529.h>
#include "iv_basic.h"
#include "iv_rcm.h"
#include "iv_v_meas.h"
#include "iv_temp.h"

void rcm(void)
{
    v_meas();
    temp();
}

void rcm_run(void)
{
    if(flag_TA2_0 == 1)
    {
        flag_TA2_0 = 0;
        adc_start();
    }

    switch(rc_sel)
    {
    case FWD: go_straight(V_STT); break; // forward
    case BWD: backward(); break; // backward
    case LWD: turn(LEF); break; // leftward
    case RWD: turn(RIT); break; // rightward
    case ACC: acc(); break; // accelerate
    case VSH: vt_sel = V_SH; break; // velocity show
    case DSH: vt_sel = D_SH; break; // temperature show
    default: break;
    }
}
