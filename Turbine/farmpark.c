/***************************************************************************
**
** Author: Neil Cherry <ncherry@linuxha.com>
** Date  : 09/12/2006
** Notes:
**
** This code is built around the SDCC compiler.
**
** This program accepts serial input on the RX line (RS232 or RS485 we
** don't care) and displays it on the LED display. The format of the
** receive string is as follows:
**
** <ID><char><char><char><char><char>
**
** Where <ID> is an ASCII character A-D or X (X is the general broadcast
** that all devices listen for.
**
** Where <char> should be a number (0-9), a '.', '-', '_' or space. Every-
** thing else is an error and displayed as a '-'.  If the valid sting ends
** up being short for some reason (such as an error) then a new valid <ID>
** (for this device) or an ID of X will reset the buffers. After 5
** characters have been sent the results will be sent to the display.
**
***************************************************************************/

#include <at89x051.h>		// AT89C2051
#include <stdio.h>

#include "local.h"

extern void display(byte *buff);

char init[] = { '-', '-', '-', '-', '.' };

/*------------------------------------------------------------------------
  main - Simple test program to send out something to the serial port.
|------------------------------------------------------------------------*/

void main(void) {
  bit me     = 0;
  bit toggle = 0;

  uchar chr;

  byte lbuf[10];  // this is our line buffer, chars gather here till CR seen
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

#if DEBUG
  putstr("Hello\r\n");
#endif
  display(init);		// Display something so I you're alive

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
#if DEBUG
      putchar(chr);		// echo back out as serial tx data
#endif
      // This routine will handle the ID (defined in the make file) or X
      // which is a general broadcast (every device). If this device doesn't
      // get the ID and 5 characters then the next ID will reset the pointers
      if(ID == chr || 'X' == chr) {
	me  = 1;
	idx = 0;		// Don't record the ID character
      } else if(me){ 		// Record if it's me
	// --------------------
	lbuf[idx] = chr;	// copy it into the buffer

	if (idx < 4){		// 4 digits and the decimal point
	  ++idx;
	} else {
	  display(lbuf);	// Got it all, display it
	  lbuf[5] = 0;
#if DEBUG
	  // Out the serial port with the information
	  print(lbuf);
#endif
	  idx = 0;		// prepare for the next string
	  me  = 0;
	}
	// --------------------
      } else {			// Oops it's not for me
	me  = 0;		// Wasn't mine, make sure it's not me
      }
    }
  }
}

