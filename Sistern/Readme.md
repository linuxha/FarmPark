# Sistern

Yup, it's spelled wrong, should be Cistern. The mistake was made a long time ago and I must now live with it.

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

## Programmer - TL866II+

This is the TL866II+ programmer

```
#+Name: Burn Wattsview-n Sistern code
#+begin_src bash :results drawer
date
cd ${HOME}/dev/git/minipro

sudo ./miniprohex -p AT89C2051@DIP20 -r /home/njc/dev/farmpark/release/r-wattsview-n.ihx
#+end_src
```

```
#+Name: Minicomhex help
#+begin_src bash :results drawer
cd ${HOME}/dev/git/minipro
miniprohex |& less
#+end_src

#+RESULTS: Minicomhex help
:results:
miniprohex by Al Williams http://www.awce.com
Usage:
  miniprohex [--offset offset] [--unfill byte size] [--obs blksize] [--line-length length] [minipro_options] -r filename.ext
  miniprohex [--offset offset] [minipro_options] -w filename.ext

This calls minipro after converting known file types to
.bin for writing or converting bin files after reading.

--offset: Offset for file conversion (see srec_cat)
--unfill: Unfil blocks of at least size of byte (see srec_cat)
--obs: Output block size (see srec_cat)
--line-length: Output line length max (see srec_cat)

Assumes minipro and srec_cat are on the path.

Here's the minipro help:
Device required. Use -p <device> to specify a device.
minipro version 0.4dev     A free and open TL866XX programmer
Usage: minipro [options]
options:
  --list		-l		List all supported devices
  --search		-L <search>	List devices like this
  --programmer	-q <model>	Force a programmer model
					when listing devices.
					Possible values: TL866A TL866II
  --query_supported	-Q		Query supported programmers
  --presence_check	-k		Query programmer version
					currently connected.
  --get_info	-d <device>	Show device information
  --get_id		-D		Just read the chip ID
  --read		-r <filename>	Read memory
  --write		-w <filename>	Write memory
  --verify		-m <filename>	Verify memory
  --format		-f <format>	Specify file format
					Possible values: ihex, srec
  --blank_check	-b		Blank check.
					Optionally, you can use -c
					to specify a memory type
  --auto_detect	-a <type>	Auto-detect SPI 25xx devices
					Possible values: 8, 16
  --pin_check	-z		Check for bad pin contact
  --skip_erase	-e 		Do NOT erase device
  --erase		-E 		Just erase device
  --write_protect	-u 		Do NOT disable write-protect
  --no_write_protect-P 		Do NOT enable write-protect
  --skip_verify	-v		Do NOT verify after write
  --device		-p <device>	Specify device (use quotes)
  --page		-c <type>	Specify memory type (optional)
					Possible values: code, data, config
  --pulse, --vpp	-o <option>	Specify various programming options
  --vdd, --vcc
					For multiple options use -o
					for each option
					Programming voltage <vpp=value>
					*=TL866II+ only  **=TL866A/CS only
					(*9,*9.5, 10, *11, *11.5, *12, 12.5)
					(*13, 13.5, 14, *14,5, 15.5, 16)
					(*16.5, 17, 18, **21)
					VDD write voltage <vdd=value>
					VCC verify voltage <vcc=value>
					(3.3, 4, 4.5, 5, 5.5, 6.5)
					Programming pulse delay
					<pulse=value> (0-65535 usec)
  --icsp_vcc	-i		Use ICSP
  --icsp_no_vcc	-I		Use ICSP (without enabling Vcc)
  --no_size_error	-s		Do NOT error on file size mismatch
					(only a warning)
  --no_size_warning	-S		No warning message for
					file size mismatch
					(can't combine with -s)
  --skip_id		-x		Do NOT attempt to read ID
					(only valid in read mode)
  --no_id_error	-y		Do NOT error on ID mismatch
  --version		-V		Show version information
  --hardware_check	-t		Start hardware check
  --update		-F <filename>	Update firmware
					(should be update.dat or updateII.dat)
  --help		-h		Show help (this text)
:end:
```

## Other programmer - PG302

```
# /home/njc/cookie/dev.storage/farmpark/other/PG302

pg302 -p /dev/ttyUSB1 bcheck
pg302 -p /dev/ttyUSB1 erase
pg302 -p /dev/ttyUSB1 prog wattsview.ihx
pg302 -p /dev/ttyUSB1 verify wattsview.ihx
```
