top_srcdir=..

BIN=$(top_srcdir)/bin/linux/

CC = $(BIN)cc68
CRT0=crt0.o
LD = $(CC)
AS = $(CC)

all: gistdrvr.prg

.c.o:
	$(AM_V_CC)$(CC) $(CFLAGS) $(CPPFLAGS) ${RUN_OPTIMIZE_${$*_OPTIMIZE}} -c -o $@ $<

gistdrvr.prg: install.o sndsubs.o sndint.o osbind.o ${MAKEFILE}
	$(AM_V_LD)$(LD) $(LDFLAGS) -u -s -h 0 -o $@ install.o sndsubs.o sndint.o osbind.o $(LIBS)

clean::
	rm -f *.o gistdrvr.prg
