# Sistern

wattsview-n - Sistern
wattsview - Feats of Strength

Version: --2.1

2 turns of the wire and display 0.0 when less than 2W.

Source code related to the Wattsview and the Sistern display

Field separator: space (0x20), \r (CR - 0xoD), or \n (LF - 0x0A)

```
Expected input:  000012.1V 00001.0A 00012.1W 00000.0WH\r\n
Expected output:  12.1

or
Expected input:  OFF\r\n
Expected output: _OFF
```

## Notes
```
njc@mozart:~/dev/farmpark/release$ make wattsview-n
sdcc -mmcs51 --model-small --iram-size 128 -o wattsview-n.rel -c wattsview-n.c
sdcc -mmcs51 --model-small --iram-size 128 wattsview-n.rel display.rel  -o wattsview-n.ihx
packihx wattsview-n.ihx > wattsview-n.hex
packihx: read 217 lines, wrote 132: OK.
echo "89C2051 has 0x800 of flash and  128 bytes of ram"
89C2051 has 0x800 of flash and  128 bytes of ram
cat wattsview-n.mem
Internal RAM layout:
      0 1 2 3 4 5 6 7 8 9 A B C D E F
0x00:|0|0|0|0|0|0|0|0|a|a|a|a|a|a|a|a|
0x10:|a|a|a|a|a|a|a|a|a|a|a|a|a|a|a|a|
0x20:|a|a|a|a|a|a|a|a|a|a|a|a|a|a|a|a|
0x30:|Q|Q|Q|Q|S|S|S|S|S|S|S|S|S|S|S|S|
0x40:|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|
0x50:|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|
0x60:|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|
0x70:|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|S|
0x80:| | | | | | | | | | | | | | | | |
0x90:| | | | | | | | | | | | | | | | |
0xa0:| | | | | | | | | | | | | | | | |
0xb0:| | | | | | | | | | | | | | | | |
0xc0:| | | | | | | | | | | | | | | | |
0xd0:| | | | | | | | | | | | | | | | |
0xe0:| | | | | | | | | | | | | | | | |
0xf0:| | | | | | | | | | | | | | | | |
0-3:Reg Banks, T:Bit regs, a-z:Data, B:Bits, Q:Overlay, I:iData, S:Stack, A:Absolute

Stack starts at: 0x34 (sp set to 0x33) with 76 bytes available.

Other memory:
   Name             Start    End      Size     Max
   ---------------- -------- -------- -------- --------
   PAGED EXT. RAM                         0      256
   EXTERNAL RAM                           0    65536
   ROM/EPROM/FLASH  0x0000   0x061e    1567    65536
njc@mozart:~/dev/farmpark/release$ type sdcc
sdcc is /usr/bin/sdcc
njc@mozart:~/dev/farmpark/release$ sdcc -v
SDCC : mcs51/z80/z180/r2k/r3ka/gbz80/tlcs90/ds390/TININative/ds400/hc08/s08/stm8 3.8.0 #10562 (Linux)
published under GNU General Public License (GPL)
njc@mozart:~/dev/farmpark/release$ 
```
