# FarmPark

Various code related to Displays at various parks. This document will change as I get more time to clean it up properly.

## Turbine

Source code and directory structure for code related to the Turbine project

## Feats

Source code related to Wattsview and the Feats of Strength display

## Sistern

Source code related to the Wattsview and the Sistern display

## sdcc

SDCC needed to compile 89Cx051 code used in the 4x7 Segement LED Displays

## Tmp notes

sdcc 2.6.0 is now configured for

  Build:
  Host:
  Source directory:     .
  C compiler:           gcc
  CFLAGS:               -pipe -ggdb -g -O2

  ENABLED Ports:
    avr                 yes
    ds390               yes
    ds400               yes
    gbz80               yes
    hc08                yes
    pic                 yes
    pic16               yes
    xa51                yes
    z80                 yes

  Disable packihx:      0
  Disable ucsim:        0
  Disable device lib:   0
  Disable sdcpp:        0
  Enable documentation: 0
  Enable libgc:         0

  Install paths:
    binary files:       ${prefix}
    include files:      ${prefix}/share/sdcc/include
    library files:      ${prefix}/share/sdcc/lib
    documentation:      ${datadir}/sdcc/doc

    prefix:             /usr/local
    datadir:            ${prefix}/share

  Search paths (incomplete, see manual for all search paths):
    binary files:       $SDCC_HOME/bin
    include files:      /share/sdcc/include
                        path(argv[0])/../share/sdcc/include
                        /usr/local/share/sdcc/include
    library files:      $SDCC_HOME/share/sdcc/lib/<model>
                        path(argv[0])/../share/sdcc/lib/<model>
                        /usr/local/share/sdcc/lib/<model>

/home/njc/t/cookie/dev.storage/farmpark/other/sdcc

APPLICATION NOTE 3477
USING THE FREE SDCC C COMPILER TO DEVELOP FIRMWARE FOR THE DS89C430/450 FAMILY OF MICROCONTROLLERS
https://www.maximintegrated.com/en/design/technical-documents/app-notes/3/3477.html
