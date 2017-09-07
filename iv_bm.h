/*
 * iv_bm.h
 *
 *  Created on: 2017Äê9ÔÂ5ÈÕ
 *      Author: ASUS
 */

#ifndef IV_BM_H_
#define IV_BM_H_

void bm(void);
void bm_ISR(void);
void bm_run(void);
__interrupt void TIMER2_A1_ISR(void);

#endif /* IV_BM_H_ */
