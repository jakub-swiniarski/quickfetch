SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

qf: $(OBJECTS)
	gcc -o qf $(OBJECTS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	gcc -c $(SOURCES)

.PHONY: clean run install uninstall

clean:
	rm *.o qf

run: qf
	./qf

install: qf
	cp qf /usr/bin/

uninstall:
	rm /usr/bin/qf
