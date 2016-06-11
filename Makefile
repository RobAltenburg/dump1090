CFLAGS?=-O2 -g -Wall -W $(shell pkg-config --cflags librtlsdr)
LDLIBS+=$(shell pkg-config --libs librtlsdr) -L/usr/local/lib -lpthread -lm -lsqlite3
CC?=clang
PROGNAME=dump1090

all: dump1090

%.o: %.c
	$(CC) $(CFLAGS) -c $<

dump1090: dump1090.o anet.o database.o
	$(CC) -g -o dump1090 dump1090.o anet.o database.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *.o dump1090
