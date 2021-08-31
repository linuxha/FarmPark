#
# Farmpark display make file.
#
# Author:   Neil Cherry (ncherry@linuxha.com)
# Date:     09/12/2006
# Compiler: SDCC 2.6.0 #4309 (Unix/Windows)
#

# ----------------------------------------------------------------------------
PATH:=/opt/sdcc-2.6.0/bin:${PATH}:/home/njc/cookie/dev.storage/farmpark/other/PG302
SDCC_HOME=/opt/sdcc-2.6.0

#COPT	= -mmcs51 --model-small --stack-size 32 -D"ID=\'A\'"
COPT	= -mmcs51 --model-small --iram-size 128
OPT	= -mmcs51 --model-small --iram-size 128
CC	= sdcc

VER	= 1.0

# ----------------------------------------------------------------------------
%.ihx : %.rel
	$(CC)  $(COPT) $^

%.rel : %.c local.h
	$(CC) $(COPT) -c $<
# ----------------------------------------------------------------------------

all:	farmparkA farmparkB farmparkC farmparkD

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

wattsview-n.rel : wattsview-n.c local.h
	$(CC) $(OPT) -o $@ -c $<

# ----------------------------------------------------------------------------
burn:
	@echo /home/njc/cookie/dev.storage/farmpark/other/PG302
	@echo
	@echo pg302 -p /dev/ttyUSB1 bcheck
	@echo pg302 -p /dev/ttyUSB1 erase
	@echo pg302 -p /dev/ttyUSB1 prog wattsview.ihx
	@echo pg302 -p /dev/ttyUSB1 verify wattsview.ihx
	pg302

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
