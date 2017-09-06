/*
 * iv_digit.c
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: ASUS
 */
#include <msp430.h>
#include "iv_digit.h"

// normal 0-9
unsigned char SEG[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
// 0-9 with ':'
unsigned char COLONSEG[] = {0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef};
 /**
  * main.c
  */
void TM1637_start(void)
{
    // set to output
    CLKO;
    DIOO;

    CLKH;
    DIOH;
    __delay_cycles(1120); // 140us
    DIOL;
    __delay_cycles(1120); // 140us
    CLKL;
    __delay_cycles(1120); // 140us
}

void TM1637_stop(void)
{
    CLKL;
    __delay_cycles(1120); // 140us
    DIOL;
    __delay_cycles(1120); // 140us
    CLKH;
    __delay_cycles(1120); // 140us
    DIOH;
    __delay_cycles(1120); // 140us
}

void TM1637_bitwrite(unsigned char mbit)
{
    CLKL;
    __delay_cycles(1120); // 140us
    if(mbit)
        DIOH;
    else
        DIOL;
    __delay_cycles(1120); // 140us
    CLKH;
    __delay_cycles(1120); // 140us
}

void TM1637_bytewrite(unsigned char mbyte)
{
    unsigned int i;
    for(i = 0; i < 8; i++)
    {
        TM1637_bitwrite((mbyte >> i) & BIT0);
    }
    CLKL;
    __delay_cycles(1120); // 140us
    DIOH;
    __delay_cycles(1120); // 140us
    CLKH;
    __delay_cycles(1120); // 140us
    DIOI;
    while(DIOV); // get response
    DIOO;
}

void TM1637_cmdwrite(unsigned char mcmd)
{
    TM1637_start();
    TM1637_bytewrite(mcmd);
    TM1637_stop();
}

void TM1637_datawrite(unsigned char addr, unsigned char mdata)
{
    TM1637_start();
    TM1637_bytewrite(addr);
    TM1637_bytewrite(mdata);
    TM1637_stop();
}

void digit_display(unsigned char hh, unsigned char hl, unsigned char lh, unsigned char ll)
{
    TM1637_cmdwrite(0x44);
    TM1637_datawrite(0xc0, SEG[hh]);
    TM1637_datawrite(0xc1, SEG[hl]);
    TM1637_datawrite(0xc2, SEG[lh]);
    TM1637_datawrite(0xc3, SEG[ll]);
    TM1637_cmdwrite(0x8a);
}

void time_display(unsigned char hh, unsigned char hl, unsigned char lh, unsigned char ll)
{
    TM1637_cmdwrite(0x44);
    TM1637_datawrite(0xc0, SEG[hh]);
    TM1637_datawrite(0xc1, COLONSEG[hl]);
    TM1637_datawrite(0xc2, SEG[lh]);
    TM1637_datawrite(0xc3, SEG[ll]);
    TM1637_cmdwrite(0x8a);
}

void n_display(unsigned int x)
{
    unsigned int i, d[4];
    for(i = 0; i < 4; i++)
    {
        d[i] = x % 10;
        x /= 10;
    }
    digit_display(d[3], d[2], d[1], d[0]);
}

