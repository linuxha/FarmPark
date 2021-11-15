#!/bin/bash

if [ $# -ne 0 ]; then
    echo "All is lost, there is no help"
    echo "Expects the display to be on /dev/ttyS0"
    echo "Spits out a set of numbers"

    exit 1
fi

STR='00001.9W
99999.9W
87654.3W
76543.2W
65432.1W
00000.0W
00009.9W
00099.9W
00999.9W
09999.9W
99999.9W
00123.4W
00032.1W
00321.9W
03219.8W
32198.7W
321987.6W
00002.1W
00003.2W
00001.9W
'

# A WattView message:
#        0        9        8        7         7
#        000012.1V 00001.0A 00012.1W 00000.0WH\r\n
#
# COMMUNICATION STANDARD RS232 – SERIAL COMMUNICATIONS 9600 BAUD, 8 Data bits, No Parity,
#                                No Flow Control. (Three wires used: Tx, Rx, Gnd)

stty -F /dev/ttyS0 9600

for str in $STR
do
    # Needs that space after the string or it will be ignored by the display
    echo "${str} " | tee /dev/ttyS0
    sleep 3
done
