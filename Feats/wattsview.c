/***************************************************************************
**
** Author: Neil Cherry <ncherry@linuxha.com>
** Date  : 2013/01/01
** Notes: Accepts RS232 input from Wattsview power board
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

char init[] = { "--1.0" };	// 2 Turn Version

/*
** 2 Turn version
**
** This version works with the Wattsview power meter board and is set
** for when there are 2 turns of the wire through the toroid.
*/

const char prog[] = "watttsview display 123";
/*------------------------------------------------------------------------
  main - 
|------------------------------------------------------------------------*/

#define MAXLEN	40

void main(void) {
  bit me     = 0;
  bit toggle = 0;

  uchar chr;

  byte buf[MAXLEN];  // this is our line buffer, chars gather here till CR seen
  byte idx   = 0;


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
    // You can pulse !ST more often than 62.5ms!!!
    //
    // -----------------------------------------------------------------------
    ST = 1;
    ST = 0;
    //ST = 1;
    // -[ end ]---------------------------------------------------------------

    if (RI) {			// we have new serial rx data
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
      // **  00012.1W
      // **  00000.0WH
      // ** Read a character, store it in an array until we match the

      // Word seperators: SPACE, CR, NL
      if(chr == ' ' || chr == '\r' || chr == '\n') {
	char *ptr;
	//
	buf[idx] = 0;		// Terminate the buffer

	/*
	  00000.1W

	      +-buf[2]
	      V
	  0 0 0 0 0.1W
	  [ x.x.x.x.]
	  [       0.]
	  [     0 0.]       0
	  [     0.9 ]     0.9
	  [     9.9 ]     9.9
	  [   1 0.0 ]    99.9
	  [ 9 9 9.9 ]   999.9
	  [ 9 9 9 9.]  9999.
	  [ 0 1 0.0 ]  __10.0  10.0K 10000
	  [ 0 9 9.9 ]  __99.9  99.9K 99999
	*/

	// WH also has a W @ position 7
	if(buf[idx-1] == 'W') {
	  ptr = &buf[2];
	  buf[7] = 0;

	  if(buf[0] != '0') {		// > 9999.
	    // 012
	    // 99999.9
	    // ___99.9k
	    buf[6] = buf[2];
	    buf[4] = buf[1];
	    buf[3] = buf[0];
	    buf[2] = '_';
	    buf[1] = '_';

	    buf[0] = 'A';

	    ptr = &buf[1];
	  } else if(buf[1] != '0') {
	    // 09999.9
	    //  9999.9
	    buf[5] = 0;		// Drop every right of the decimal point (inclusive)

	    buf[0] = 'B';

	    ptr = &buf[1];
	  } else if(buf[2] != '0') {
	    // 00999.9
	    //   999.9
	    buf[1] = ' ';		// left justify with spaces

	    buf[0] = 'C';

	  } else if(buf[3] != '0') {
	    // 00099.9
	    //    99.9
	    buf[1] = ' ';		// left justify with spaces
	    buf[2] = ' ';

	    buf[0] = 'D';

	  } else { // if(buf[4] != '0') {
	    // 00009.9
	    //     9.9
	    buf[1] = ' ';		// left justify with spaces
	    buf[2] = ' ';
	    buf[3] = ' ';

	    buf[0] = 'E';
	  }

	  display(ptr);
	} else if(buf[idx-1] == 'F') { // if 'W'
	  ptr = " 0?? "; // translates to OFF

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

