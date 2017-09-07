/*
 * iv_ob_avoid.h
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: ASUS
 */

#ifndef IV_OB_AVOID_H_
#define IV_OB_AVOID_H_

extern unsigned int num1, num2;
extern unsigned int cycle1[], cycle2[];
/*
 * automatic obstacle avoidance
 * strategy: detect right then turn left, left then right,
 * both then stop
*/

inline void buzzer_update(unsigned int beep)
{
    if(beep)
        P3OUT |= BIT0;
    else
        P3OUT &= ~BIT0;
}
void ob_avoid(void);
void ob_avoid_ISR(void);
__interrupt void TIMER1_A0_ISR(void);
__interrupt void TIMER1_A1_ISR(void);



#endif /* IV_OB_AVOID_H_ */
