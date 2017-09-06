/*
 * iv_temp.h
 *
 *  Created on: 2017Äê9ÔÂ5ÈÕ
 *      Author: ASUS
 */

#ifndef IV_TEMP_H_
#define IV_TEMP_H_

inline void adc_start(void)
{
    ADC12CTL0 |= ADC12SC; // start ADC
}
void temp(void);
__interrupt void ADC12_ISR(void);

#endif /* IV_TEMP_H_ */
