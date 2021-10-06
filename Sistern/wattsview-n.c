/***************************************************************************
**
** Author: Neil Cherry <ncherry@linuxha.com>
** Date  : 2013/01/28
** Notes : Accepts RS232 input from Wattsview power board
**
** Name  : Wattsview-n
**
**        it's output looks like this:
**        0        9        8        7         7
**        000012.1V 00001.0A 00012.1W 00000.0WH\r\n
**        000012.1V
**         00001.0A
**         00012.1W
**         00000.0WH
**
** This code is built around the SDCC compiler.
**
**
***************************************************************************/

#include <at89x051.h>		// AT89C2051
#include <stdio.h>

#include "local.h"

extern void display(byte *buff);

char init[] = { "--2.1" };	// 2 Turn Version

/*
** 2 Turn version
**
** This version works with the Wattsview power meter board and is set
** for when there are 2 turns of the wire through the toroid.
*/

const char prog[] = "watttsview-n 2 turn";

// ---------------------------------------------------------------------------
// A quick ASCII to long x10
// We get 12345.6
// We return 123456 (note the lack of a decimal point)
// we need to support 999999 (> 64k) so it needs to be a long
long myAtol(char *str) {
  byte x = 0;
  static long l;

  l = 0;

  while(*str != 0 && x < 10) {
    if(*str != '.') {
      l = l * 10;
      l = l + (*str - '0');
    }

    x++;
    str++;
  }

  return(l);
}

// modulo - a%b
int mod(int a, int b) {
  // a - (b * int(a/b));
  int modulo;

  modulo = a - (b * (a/b));

  return(modulo);
}

const char lookup[] = "0123456789abcdef";

// This is a special instance of itoa, it converts the 
char* myItoa(int x, int y) {
  static char buf[12] = {0};
  int a = x;
  int b = y;

  int i = 10;
  int digits;

  // 4 places
  for(digits = 4; ((y || digits) && i) ; y /= 10) {
    buf[i] = lookup[y % 10];

    --digits;
    --i;
  }

  buf[i] = '.';
  --i;

  if(x) {
    if(x < 10) {
      digits = 1; // Single digit
    } else {
      digits = 2; // Double digit
    }
    for(; ((x || digits) && i) ; x /= 10) {
      buf[i] = lookup[x % 10];
      --i;
      --digits;
    }
  } else {
    buf[i] = '0';
    --i;
  }
  i++;

  return &buf[i];
}

// ---------------------------------------------------------------------------

/*------------------------------------------------------------------------
  main - 
|------------------------------------------------------------------------*/

#define MAXLEN	12

void main(void) {
  bit me     = 0;
  bit toggle = 0;

  uchar chr;

  byte buf[MAXLEN];  // this is our line buffer, chars gather here till CR seen
  byte idx   = 0;

  int iValue;
  int iTmp;
  int l;

  // -[ Serial Port ]---------------------------------------------------------
  PCON = 0x80;  // power control byte, set SMOD bit for serial port
  SCON = 0x50;  // serial control byte, mode 1, RI active

  TMOD = 0x20;  // T0 - 13 bit mode, T1 8 bit reload

  TCON = 0;     // timer control register, byte operation

  TH1  = 0xFA;  // serial reload value, 9,600 baud at 11.0952Mhz
  TR1  = 1;     // start serial timer

  EA   = 1;     // Enable Interrupts

  TI   = 0;     // clear this out
  // -------------------------------------------------------------------------

  ST = 1;			// Watchdog pulse active low, default it to high
  ST = 0;
  //ST = 1;

  buf[MAXLEN-1] = 0;

  display(init);		// Display something so I know you're alive

  for (;;) {
    // -[ Watchdog ]----------------------------------------------------------
    // This is for the MAX1232 watchdog chip
    // !ST
    //             tTD
    //  ___    ___...___    ___
    //     |___|        |___|
    //      tST
    //
    // 1 instruction = 11.0592 MHz /12 = 1.0851 us (0.000001085069444 s)
    //
    // tST !ST min pulse  = 75ns
    //
    //              Min   Typ   Max
    //                     ms
    //------------------------------
    // tTD = 0V   | 62.5  150   250
    //     = Open | 250   600  1000
    //     = Vcc  | 500  1200  2000
    //------------------------------
    //
    // You can pulse !ST more often than 62.5ms!!! (about 16Hz)
    //
    // -----------------------------------------------------------------------
    ST = 1;
    ST = 0;
    //ST = 1;
    // -[ end ]---------------------------------------------------------------

    if (RI) {			// we have new serial rx data
      // Character is an ASCII character ie 1 is 0x31
      chr = SBUF;		// read the serial char
      RI = 0;			// reset serial rx flag

      /*
      ** We're in the for look
      */

      // --[ New code ]-------------------------------------------------------
      // **
      // ** 0        9        8        7         7
      // ** 000012.1V 00001.0A 00012.1W 00000.0WH\r\n
      // ** 000012.1V
      // **  00001.0A
      // **  00012.1W  <- string of interest
      // **  00000.0WH
      // ** Read a character, store it in an array until we match the
      // **  OFF

      // Word separators: SPACE, CR, NL
      if(chr == ' ' || chr == '\r' || chr == '\n') {
	// Okay now we've got the Watts used as a string
	char *ptr;

	//
	buf[idx] = 0;		// Terminate the buffer

	// Our string ends in W
	// WH also has a W @ position 7 but ends in H
	// So use idx-1 to determine the string

	if(buf[idx-1] == 'W') {

	  // Make sure we null terminate at the W
	  buf[7] = 0;

	  // Integer: 123456 (Watts x10)
	  l = myAtol(buf); // value x10
	  // Divide by 2 for the 2:1 ratio
	  l = l >> 1;

	  // We're doing integer math so *10 to get rid of the decimal point
	  // and div by 1000x10 to get KW
	  // gives us
	  // iValue.iTmp (where iTmp is 4 places long)
	  iValue  = l/10000;

          // Bob W. asked that <2W be 0.0W 2021104
          if(l < 2) {
              iValue = 0; // Correction for <2W
              iTmp   = 0;
          } else {
              iTmp    = mod(l, 10000);
          }
          // String:  12.34  (KWatts, left justify)
          ptr = myItoa(iValue, iTmp);

              // Back to a string
	  display(ptr);
	} else if(buf[idx-1] == 'F') { // if 'W'
	  ptr = " 0?? "; // translates to OFF

	  // Back to a string
	  display(ptr);
	} // if 'F'

	idx = 0;
      } else {
	//
	buf[idx] = chr;
	idx++;
      }

      if(idx > MAXLEN) {
	buf[MAXLEN-1] = 0;
	idx = 0;
      }

      // --[ End New code ]---------------------------------------------------
    } // RI
  } // --[ for(;;) ]----------------------------------------------------------
}
