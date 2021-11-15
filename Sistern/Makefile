#
# Farmpark display make file.
#
# Author:   Neil Cherry (ncherry@linuxha.com)
# Date:     09/12/2006
# Compiler: SDCC 2.6.0 #4309 (Unix/Windows)
#

# ----------------------------------------------------------------------------
export PATH:=/opt/sdcc-2.6.0/bin:${PATH}:/home/njc/cookie/dev.storage/farmpark/other/PG302:/home/njc/dev/git/minipro:
BPATH   = /home/njc/dev/git/minipro
SDCC_HOME=/opt/sdcc-2.6.0

#COPT	= -mmcs51 --model-small --stack-size 32 -D"ID=\'A\'"
COPT	= -mmcs51 --model-small --iram-size 128 -V
OPT	= -mmcs51 --model-small --iram-size 128 -V
CC	= sdcc

VER	= 1.0

# ----------------------------------------------------------------------------
%.ihx : %.rel
	$(CC)  $(COPT) $^

%.rel : %.c local.h
	$(CC) $(COPT) -c $<
# ----------------------------------------------------------------------------

#all:	farmparkA farmparkB farmparkC farmparkD
all:	wattsview-1

# ============================================================================
clean:
	rm -rf *~ *.asm *.ihx *.lst *.map *.mem *.rel *.rst   \
		*.sym foo bar *.d51 *.hex *.a51 *.lnk

tidy:
	rm -rf *~ *.asm *.ihx *.lst *.map *.mem *.rel *.rst   \
		*.sym foo bar *.d51 *.a51 *.lnk

bak:	clean
	cd ..; rm -rf farmpark-$(VER).tgz ; tar -zvcf farmpark-$(VER).tgz farmpark

# ----------------------------------------------------------------------------
farmparkA: farmparkA.ihx
	packihx $^ > $@.hex

farmparkA.ihx:	farmparka.rel display.rel
	$(CC) $(COPT) $^ -o $@

farmparka.rel : farmpark.c local.h
	$(CC) $(OPT) -D"ID=\'A\'" -o $@ -c $<

# ----------------------------------------------------------------------------
farmparkB: farmparkB.ihx
	packihx $^ > $@.hex

farmparkB.ihx:	farmparkb.rel display.rel
	$(CC) $(COPT) $^ -o $@

farmparkb.rel : farmpark.c local.h
	$(CC) $(OPT) -D"ID=\'B\'" -o $@ -c $<

# ----------------------------------------------------------------------------
farmparkC: farmparkC.ihx
	packihx $^ > $@.hex

farmparkC.ihx:	farmparkc.rel display.rel
	$(CC) $(COPT) $^ -o $@

farmparkc.rel : farmpark.c local.h
	$(CC) $(OPT) -D"ID=\'C\'" -o $@ -c $<

# ----------------------------------------------------------------------------
farmparkD: farmparkD.ihx
	packihx $^ > $@.hex

farmparkD.ihx:	farmparkd.rel display.rel
	$(CC) $(COPT) $^  -o $@

farmparkd.rel : farmpark.c local.h
	$(CC) $(OPT) -D"ID=\'D\'" -o $@ -c $<

# ----------------------------------------------------------------------------
wattsview: wattsview.ihx
	packihx $^ > $@.hex
	@echo "89C2051 has 0x800 of flash and  128 bytes of ram"
	cat $@.mem

wattsview.ihx:	wattsview.rel display.rel
	$(CC) $(COPT) $^  -o $@

wattsview.rel : wattsview.c local.h
	$(CC) $(OPT) -D"ID=\'D\'" -o $@ -c $<

# 
wattsview-n:	wattsview-n.ihx
	packihx $^ > $@.hex
	echo "89C2051 has 0x800 of flash and  128 bytes of ram"
	cat $@.mem

wattsview-n.ihx:	wattsview-n.rel display.rel
	$(CC) $(COPT) $^  -o $@

wattsview-n.rel:	wattsview-n.c local.h
	$(CC) $(OPT) -o $@ -c $<

# 
wattsview-1:	wattsview-1.ihx
	packihx $^ > $@.hex
	echo "89C2051 has 0x800 of flash and  128 bytes of ram"
	cat $@.mem

wattsview-1.ihx:	wattsview-1.rel display.rel
	$(CC) $(COPT) $^  -o $@

wattsview-1.rel:	wattsview-n.c local.h
	$(CC) $(OPT) -DONETURN -DXMIT -o $@ -c $<

# 
wattsview-2:	wattsview-2.ihx
	packihx $^ > $@.hex
	echo "89C2051 has 0x800 of flash and  128 bytes of ram"
	cat $@.mem

wattsview-2.ihx:	wattsview-2.rel display.rel
	$(CC) $(COPT) $^  -o $@

wattsview-2.rel:	wattsview-n.c local.h
	$(CC) $(OPT) -DTWOTURN -o $@ -c $<

# ----------------------------------------------------------------------------
burn:
	@echo /home/njc/cookie/dev.storage/farmpark/other/PG302
	@echo
	@echo pg302 -p /dev/ttyUSB1 bcheck
	@echo pg302 -p /dev/ttyUSB1 erase
	@echo pg302 -p /dev/ttyUSB1 prog wattsview.ihx
	@echo pg302 -p /dev/ttyUSB1 verify wattsview.ihx
	pg302

burn-1:	wattsview-1.ihx
	@echo Burn 1 Turn code
	@echo "Current Working Directory: ${PWD}"
	cd $(BPATH); sudo ./miniprohex -p AT89C2051@DIP20 -w ${PWD}/$< ; echo $$?

burn-2:	wattsview-2.ihx
	echo Burn 2 Turn code
	cd $(BPATH); sudo ./miniprohex -p AT89C2051@DIP20 -w /home/njc/dev/farmpark/release/$< ; echo $$?

# 1042  /home/njc/dev/pg302/src/pg302 -l usb1
# 1043  /home/njc/dev/pg302/src/pg302
# 1044  pg302 -p /dev/ttyUSB1 
# 1045  pg302 -p /dev/ttyUSB1 bcheck
# 1046  pg302 -p /dev/ttyUSB1 erase
# 1047  pg302 -p /dev/ttyUSB1 xsum
# 1048  pg302 -p /dev/ttyUSB1 prog wattsview.ihx 
# 1049  pg302 -p /dev/ttyUSB1 verify wattsview.ihx 
# 1050  pg302 -p /dev/ttyUSB1 foo.ihx 
# 1051  pg302 -p /dev/ttyUSB1 read foo.ihx 
# 1052  sum foo.ihx wattsview.ihx 
# 1053  history

# ----------------------------------------------------------------------------
test:
	@echo "Path:"
	@echo ${PATH}

check:
	which sdcc

help:
	@echo -e 'Use:\n\tmake - to compile to hex\n\tmake clean - to clean up all the files\n\tmake tidy - to clan up but leave the .hex file\n\tmake bak - to clean up (no .hex) and create a tar.gz backup\n\tmake burn - burn .ihx file (pg302)\n\tmake burn-1 - burn .ihx file (miniprohex)'
