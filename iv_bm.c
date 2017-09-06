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

void bm(void)
{
    // set the rear ultrasonics


    // other simultaneous functions
    v_meas();
    temp();
}

void bm_run()
{

}
