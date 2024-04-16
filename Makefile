SRC = $(wildcard *.c)
HDR = $(wildcard *.h)
OBJ = $(SRC:.c=.o)

qf: $(OBJ)
	gcc -o $@ $(OBJ)

$(OBJ): $(SRC) $(HDR)
	gcc -c $(SRC) -std=c99 -pedantic -Wall -Wno-deprecated-declarations -O2

.PHONY: clean run install uninstall

clean:
	rm *.o qf

run: qf
	./qf

install: qf
	cp qf /usr/local/bin/

uninstall:
	rm /usr/local/bin/qf
