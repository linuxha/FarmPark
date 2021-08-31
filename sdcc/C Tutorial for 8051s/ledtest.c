// Iguana Labs
// First C example for 8051s
// 3/19/04

/*-----------------------------------------------------------------------------
Definitions for Ports. Ports are considered Special Function Registers. These
registers have specific locations in memory. The statements below tell the 
compiler what memory address to use for each SFR specified.
-----------------------------------------------------------------------------*/
sfr P0 = 0x80;        /* SFR for Port 0 */
sfr P1 = 0x90;        /* SFR for Port 1 */
/*-----------------------------------------------------------------------------*/

void main (void)
  {
  unsigned char x=0;              
  unsigned int y;              // y is an integer counter

  while (1)                    // Endless Loop
     {                        
      if (x==0) {x=255;} else {x=0;}   // switch x between 0 (00000000) and 255 (11111111)
	  P0 = x;                          // move x to Port 0
      P1 = x;                          // move x to Port 1
      for (y = 0; y < 10000; y++)      // simple delay routine
         { ; }
     }
  }
