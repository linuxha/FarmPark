/***************************************************************************
**
** Author: Neil Cherry <ncherry@linuxha.com>
** Date  : 09/12/2006
** Notes:
**
** This code is built around the SDCC compiler.
**
***************************************************************************/

#ifndef MYLOCAL_H
#define MYLOCAL_H

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#define RAM_SIZE        128     // 128 bytes of ram
#define RAM_TOP         128     // Top of RAM
#define ROM_TOP         2048    // Top of ROM

sfr  at 0x80 P0;		// Special function register P0 at location 0x80
sbit at 0xd7 CY;		// CY (Carry flag)

/* P1 */
sbit at 0x90 SI;		// P1_0 connect to pin 14 of the 74HC595
sbit at 0x91 RCK ;		// P1_1 connect to pin 12 of the 74HC595
sbit at 0x92 SCK ;		// P1_2 connect to pin 11 of the 74HC595

// ShiftOut Explanation:
//
// Deciding PRE or POST is a device specific matter. Below is the
// timing diagram for the 74HC595. The SRCLK is our clock pulse and
// SER is our data. If you look at the timings you will see that a
// clock pulse always comes before the data. Since this is the case we
// use PRE which means before. So the PRE indicates a clock pulse
// before the data and POST means data before the clock.
//
// The last part of our timing diagram shows the timings for the
// RCLK. The RCLK controls the 74HC595 internal latch. We use the
// PULSOUT command to trigger the latch with a 8us pulse. A pulse as
// little as 4us would work also.
//
// Sometimes data sheets are a little intimidating. In most cases when
// using the SHIFTIN / SHIFTOUT commands you will only need to glance
// at the timing diagrams to figure out which mode to use.
//         _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _ 
// SRCLK _| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_
//           ___                                     ___
// SER   ___|   |___________________________________|   |_________________
//               _   _   _   _   _   _   _   _   _       _           _
// RCLK  _______| |_| |_| |_| |_| |_| |_| |_| |_| |_____| |_________| |___
//

// For c74HC595(buff)
sbit at 0x90 DATA;		// P1_0 connect to pin 14 of the 74HC595 - SER   (Serial Data)
sbit at 0x91 LATCH;		// P1_1 connect to pin 12 of the 74HC595 - RCLK  (Latch Clock)
sbit at 0x92 CLOCK;		// P1_2 connect to pin 11 of the 74HC595 - SRCLK (Shift Clock)

// For shift(n)
sbit at 0x90 DIN;		// P1_0 connect to pin 14 of the 74HC595 - SER   (Serial Data)
sbit at 0x91 LOAD;		// P1_1 connect to pin 12 of the 74HC595 - RCLK  (Latch Clock)
sbit at 0x92 CLK;		// P1_2 connect to pin 11 of the 74HC595 - SRCLK (Shift Clock)

//sbit at 0x93 P1_3 ;
//sbit at 0x94 P1_4 ;
//sbit at 0x95 P1_5 ;
//sbit at 0x96 P1_6 ;
sbit at 0x97 WATCHDOG_STROBE;	// P1_7
sbit at 0x97 ST;		// P1_7

// P3
sbit at 0x99 SER_RX_PORT;	// P3_0
sbit at 0x99 SER_TX_PORT;	// P3_1
//sbit at 0x9A P3_2;            // Int0
//sbit at 0x9B P3_3;            // Int1
//sbit at 0x9C P3_4;            // T0
//sbit at 0x9D P3_5;            // T1
sbit at 0x9D SPARE;             // T1
//sbit at 0x9E P3_6;            // Not on the 89C2051
//sbit at 0x9F P3_7;            //
sbit at 0x9F RS485_CTL;		// RS485 R/W control

#define Num_Of_Chips	4	// We have 4 7 segment display chips

// Interrupts
#define External_0	0
#define Timer_0		1
#define External_1	2
#define Timer_1		3
#define Serial		4

#define nop() _asm \
               nop \
	      _endasm;

#define BUF_SIZE	10

#define ON	1
#define OFF	0

#define CLEAR	0
#define SET	1

#define OSCILLATOR 11059200

#include "types.h"
//typedef unsigned char byte;

#endif
