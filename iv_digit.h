/*
 * iv_digit.h
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: ASUS
 */

#ifndef IV_DIGIT_H_
#define IV_DIGIT_H_

// set PINs
#define CLKP P4OUT
#define CLKB BIT1
#define DIOP P4OUT
#define DIOB BIT2

#define CLKO P4DIR|=BIT1
#define DIOO P4DIR|=BIT2
#define DIOI P4DIR&=~BIT2
#define CLKH P4OUT|=BIT1
#define CLKL P4OUT&=~BIT1
#define DIOH P4OUT|=BIT2
#define DIOL P4OUT&=~BIT2
#define DIOV P4IN==BIT2 //DIO value

// normal 0-9
extern unsigned char SEG[];
// 0-9 with ':'
extern unsigned char COLONSEG[];
 /**
  * main.c
  */
void TM1637_start(void);
void TM1637_stop(void);
void TM1637_bitwrite(unsigned char mbit);
void TM1637_bytewrite(unsigned char mbyte);
void TM1637_cmdwrite(unsigned char mcmd);
void TM1637_datawrite(unsigned char addr, unsigned char mdata);
void digit_display(unsigned char hh, unsigned char hl, unsigned char lh, unsigned char ll);
void time_display(unsigned char hh, unsigned char hl, unsigned char lh, unsigned char ll);


#endif /* IV_DIGIT_H_ */
