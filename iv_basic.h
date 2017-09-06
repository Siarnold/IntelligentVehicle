/*
 * iv_basic.h
 *
 *  Created on: 2017Äê8ÔÂ30ÈÕ
 *      Author: ASUS
 */

#ifndef IV_BASIC_H_
#define IV_BASIC_H_

// parameters about the three modes
#define CCM 0
#define BM 1
#define RCM 2

// parameters about the three flag_TA2_0 selects
#define TRAC 1
#define OBAV 2
#define TEMP 3

// parameters about the remote control
#define FWD 5 // forward
#define BWD 8 // backward
#define LWD 4 // leftward
#define RWD 6 // rightward
#define ACC 2 // accelerate
#define VSH 1 // velocity show
#define TSH 3 // temperature show

// parameters about the digit display
#define V_SH 0
#define T_SH 1

// parameters about the steer and motor
#define V_STT 8
#define V_TUR 8
#define V_ACC 35
#define V_BWD 20
#define LEF 77 // steering steer left
#define RIT 63 // right
#define STT 69 // straight
#define DIS_WARN 25

extern unsigned char mode /*= CCM*/;
extern unsigned char flag_TA2_0 /*=0*/;
extern unsigned char sel /*=0*/;
extern unsigned char rc_sel /*=FWD*/; // remote control select
extern unsigned char vt_sel /*=V_SH*/; // velocity / temperature show select

inline void go_straight(int motor)
{
    TA0CCR3 = motor; // motor
    TA0CCR4 = 0;
    TA0CCR1 = STT; // straight
}

inline void go_turn(int steer, int motor)
{
    TA0CCR3 = motor; // motor
    TA0CCR1 = steer;
}

inline void turn(int steer)
{
    TA0CCR1 = steer;
}

inline void backward()
{
    TA0CCR1 = 0;
    TA0CCR4 = V_BWD; // motor
}

inline void acc()
{
    TA0CCR3 = V_ACC;
}

inline set_buzzer()
{
    // set pin for buzzer
    P3DIR |= BIT0;    //P3.0 OUT
    P3OUT &= ~BIT0;
}

inline beep()
{
    P3OUT |= BIT0;
}

inline mute()
{
    P3OUT &= ~BIT0;
}

void set_clock(void);
void set_PWM(void);
void set_intpt_TA2(void); // interrupt TA2
__interrupt void  TIMER2_A0_ISR(void);

#endif /* IV_BASIC_H_ */
