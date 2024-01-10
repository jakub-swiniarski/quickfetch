SOURCES=qf.c
HEADERS=config.h
OBJECTS=$(SOURCES:.c=.o)

qf: $(OBJECTS)
	gcc -o qf $(OBJECTS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	gcc -c $(SOURCES) -pedantic -Wall -Wno-deprecated-declarations -O2

.PHONY: clean run install uninstall

clean:
	rm *.o qf

run: qf
	./qf

install: qf
	cp qf /usr/local/bin/

uninstall:
	rm /usr/local/bin/qf
