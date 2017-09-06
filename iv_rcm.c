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
    switch(rc_sel)
    {
    case FWD: go_straight(V_STT); break; // forward
    case BWD: go_backward(); break; // backward
    case LWD: TA0CCR1 = LEF; break; // leftward
    case RWD: TA0CCR1 = RIT; break; // rightward
    case ACC: TA0CCR3 = V_ACC; break; // accelerate
    case VSH: vt_sel = V_SH; break; // velocity show
    case TSH: vt_sel = T_SH; break; // temperature show
    default: break;
    }
}
