/***************************************************************************
**
** Author: Neil Cherry <ncherry@linuxha.com>
** Date  : 09/12/2006
** Notes:
**
** This code is built around the SDCC compiler.
**
***************************************************************************/

#include <at89x051.h>

#include "local.h"

// -[ display ]---------------------------------------------------------------
//
// Send data N byte to 74HC595
// input : Address data buffer (data is already in display format)
//
//         _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _ 
// SRCLK _| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_ SRCLK
//           ___                                     ___
// DATA  ___|   |___________________________________|   |_________________ SER
//               _   _   _   _   _   _   _   _   _       _           _
// RCLK  _______| |_| |_| |_| |_| |_| |_| |_| |_| |_____| |_________| |___ RCLK
//              ^
//              |
//              +-- Note the rising edge clocks the data into the chip
//
// SRCLK does not have to be a continuous stream of pulses except when a bit
// is being shifted into the chip. So if we get an interrupt between 'clocks'
// it doesn't matter.
// ---------------------------------------------------------------------------
//
// Qa -- dp
// Qb -- g
// Qc -- f
// Qd -- e
// Qe -- d
// Qf -- c
// Qg -- b
// Qh -- a
//
//   A  --
// F   |  |  B
//   G  --
// E   |  |  C
//   D  --
// dp o
//
// To turn on a segment send a 1 bit, to turn off a segment send a 0 bit.
//
// Pull pin low to light the LED. High to turn off the LED
//
//  Bit  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Hex
// Digit | a | b | c | d | e | f | g | dp| dp/no dp
// --------------------------------------------
//   0     1   1   1   1   1   1   0   0   FD
//   1     0   1   1   0   0   0   0   0   60
//   2     1   1   0   1   1   0   1   0   DA
//   3     0   0   0   0   1   1   0   0   F2
//   4     0   1   1   0   0   1   1   0   66
//   5     1   0   1   1   0   1   1   0   B6
//   6     1   0   1   1   1   1   1   0   BE
//   7     1   1   1   0   0   0   0   0   E0
//   8     1   1   1   1   1   1   1   0   FE
//   9     1   1   1   0   0   1   1   0   E6
//   A     1   1   1   0   1   1   1   0   DD
//   b     0   0   1   1   1   1   1   0   3D
//   C     1   0   0   1   1   1   0   0   9C
//   d     0   1   1   1   1   0   1   0   7B
//   E     1   0   0   1   1   1   1   0   9E
//   F     1   0   0   0   1   1   1   0   8E
// Space   0   0   0   1   0   0   0   0   10
// Dash    0   0   0   0   0   0   1   1   02
// Blank   0   0   0   0   0   0   0   1   00
//
//  Decimal point precedes a number
//

// 0-9,A,B,C,D,E,F
// 0-9.:,;,<,=,>,?
const byte digit[] = {
  // 0     1     2     3
  0xFC, 0x60, 0xDA, 0xF2,
  // 4     5     6     7
  0x66, 0xB6, 0xBE, 0xE0,
  // 8     9     a     b
  0xFE, 0xE6, 0xDD, 0x3D,
  // c     d     E     F
  0x9C, 0x7B, 0x9E, 0x8E,
  // blank or space
  // dash
  // dot
  0x10, 0x02, 0x00
};

#define UNDERSCORE 16
#define DASH       17
#define SPACE      18
#define DOT        '.'

/*
** display takes an arry of 4 bytes (5 if you include 1 decimal point)
*/
void
display(byte *buff) { 
  unsigned char i,k, cnt = 0;
  unsigned char c;

  LATCH = 0;
  CLOCK = 0;

  // Clear the display

  for (i = 0; i < Num_Of_Chips; i++) { // 4 chips
    c = buff[cnt];		// Copy the buffer contents

    if(c == '_') {		// It's a Underscore
      c = digit[UNDERSCORE];
    } else if(c == ' ') {	// It's a blank
      c = digit[SPACE];
    } else {
      c -= 0x30;
      if(c < 19) {		// It's a number
	c = digit[c];
      } else {
	c = digit[DASH];	// Error is a Dash
      }
    }

    // -------------------------------------
    // This takes care of the decimal issue!
    // -------------------------------------
    if(buff[cnt+1] == DOT) {
      c |= 0x01;		// turn on the decimal point (Dot)
      cnt++;			// This will get us past the decimal point
    }                           // (with the next increment)
    cnt++;			// Now that we've processed the character we
				// can increment the pointer to the next char
    // -------------------------------------

    for (k = 0; k < 8; k++) { 	  // 8 bits
      DATA    = (c & 0x80) ? 1:0; // Bit bang it (high bit)
      CLOCK   = 1;   
      c     <<= 1;		  // Shift out the high bit out
      CLOCK   = 0;
    }	
  }
  LATCH = 1;
}
