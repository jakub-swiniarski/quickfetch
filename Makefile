CC  = cc
SRC = $(wildcard *.c)
HDR = $(wildcard *.h)
OBJ = $(SRC:.c=.o)

all: qf

%.o: %.c
	$(CC) -c -std=c99 -pedantic -Wall -Wno-deprecated-declarations -O2 $<

$(OBJ): $(HDR)

qf: $(OBJ)
	$(CC) -o $@ $(OBJ)

run: all
	./qf

clean:
	rm -f *.o qf

install: all
	cp -f qf /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/qf

.PHONY: all run clean install uninstall
