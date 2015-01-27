# First pass ultra simple Makefile

SOURCES = main.cpp brackets.cpp input.cpp
HEADERS = brackets.h

brackets: $(SOURCES) $(HEADERS)
	g++ -o brackets $(SOURCES)

debug: $(SOURCES) $(HEADERS)
	g++ -g -o brackets $(SOURCES)

clean:
	rm -f *.o brackets
	
all: brackets
