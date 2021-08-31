// Standard Registers for all 8051s
sfr P0    = 0x80;
sfr P1    = 0x90;
sfr P2    = 0xA0;
sfr P3    = 0xB0;

// Definitions of individual Port bits

sbit P0_0 = P0^0;     /* SFR for P0.0 */
sbit P0_1 = P0^1;     /* SFR for P0.1 */
sbit P0_2 = P0^2;     /* SFR for P0.2 */
sbit P0_3 = P0^3;     /* SFR for P0.3 */
sbit P0_4 = P0^4;     /* SFR for P0.4 */
sbit P0_5 = P0^5;     /* SFR for P0.5 */
sbit P0_6 = P0^6;     /* SFR for P0.6 */
sbit P0_7 = P0^7;     /* SFR for P0.7 */

sbit P1_0 = P1^0;     /* SFR for P1.0 */
sbit P1_1 = P1^1;     /* SFR for P1.1 */
sbit P1_2 = P1^2;     /* SFR for P1.2 */
sbit P1_3 = P1^3;     /* SFR for P1.3 */
sbit P1_4 = P1^4;     /* SFR for P1.4 */
sbit P1_5 = P1^5;     /* SFR for P1.5 */
sbit P1_6 = P1^6;     /* SFR for P1.6 */
sbit P1_7 = P1^7;     /* SFR for P1.7 */

sbit P2_0 = P2^0;     /* SFR for P2.0 */
sbit P2_1 = P2^1;     /* SFR for P2.1 */
sbit P2_2 = P2^2;     /* SFR for P2.2 */
sbit P2_3 = P2^3;     /* SFR for P2.3 */
sbit P2_4 = P2^4;     /* SFR for P2.4 */
sbit P2_5 = P2^5;     /* SFR for P2.5 */
sbit P2_6 = P2^6;     /* SFR for P2.6 */
sbit P2_7 = P2^7;     /* SFR for P2.7 */

sbit P3_0 = P3^0;     /* SFR for P3.0 */
sbit P3_1 = P3^1;     /* SFR for P3.1 */
sbit P3_2 = P3^2;     /* SFR for P3.2 */
sbit P3_3 = P3^3;     /* SFR for P3.3 */
sbit P3_4 = P3^4;     /* SFR for P3.4 */
sbit P3_5 = P3^5;     /* SFR for P3.5 */
sbit P3_6 = P3^6;     /* SFR for P3.6 */
sbit P3_7 = P3^7;     /* SFR for P3.7 */


sfr PSW   = 0xD0;
sfr ACC   = 0xE0;
sfr B     = 0xF0;
sfr SP    = 0x81;
sfr DPL   = 0x82;
sfr DPH   = 0x83;
sfr PCON  = 0x87;
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;
sfr IE    = 0xA8;
sfr IP    = 0xB8;
sfr SCON  = 0x98;
sfr SBUF  = 0x99;

// PSW
sbit CY    = PSW^7;
sbit AC    = PSW^6;
sbit F0    = PSW^5;
sbit RS1   = PSW^4;
sbit RS0   = PSW^3;
sbit OV    = PSW^2;
sbit P     = PSW^0; //8052 only

//  Timer Control 1 Bits
sbit TF1   = TCON^7;
sbit TR1   = TCON^6;
sbit TF0   = TCON^5;
sbit TR0   = TCON^4;
sbit IE1   = TCON^3;
sbit IT1   = TCON^2;
sbit IE0   = TCON^1;
sbit IT0   = TCON^0;

//  Individual Interrupt Controls
sbit EA    = IE^7;
sbit ET2   = IE^5;
sbit ES    = IE^4;
sbit ET1   = IE^3;
sbit EX1   = IE^2;
sbit ET0   = IE^1;
sbit EX0   = IE^0;

//  IP
sbit PT2   = IP^5;
sbit PS    = IP^4;
sbit PT1   = IP^3;
sbit PX1   = IP^2;
sbit PT0   = IP^1;
sbit PX0   = IP^0;

//  Port 3 additional definitions
sbit RD    = P3^7;
sbit WR    = P3^6;
sbit T1    = P3^5;
sbit T0    = P3^4;
sbit INT1  = P3^3;
sbit INT0  = P3^2;
sbit TXD   = P3^1;
sbit RXD   = P3^0;

// SCON
sbit SM0   = SCON^7;
sbit SM1   = SCON^6;
sbit SM2   = SCON^5;
sbit REN   = SCON^4;
sbit TB8   = SCON^3;
sbit RB8   = SCON^2;
sbit TI    = SCON^1;
sbit RI    = SCON^0;

// Extra 8052 Registers
sfr T2CON  = 0xC8;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2    = 0xCC;
sfr TH2    = 0xCD;

sbit T2EX  = P1^1;
sbit T2    = P1^0;
            
//  T2CON
sbit TF2    = T2CON^7;
sbit EXF2   = T2CON^6;
sbit RCLK   = T2CON^5;
sbit TCLK   = T2CON^4;
sbit EXEN2  = T2CON^3;
sbit TR2    = T2CON^2;
sbit C_T2   = T2CON^1;
sbit CP_RL2 = T2CON^0;
