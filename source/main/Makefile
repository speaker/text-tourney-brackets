# First pass ultra simple Makefile

SOURCES = main.cpp brackets.cpp team.cpp roster.cpp match.cpp
HEADERS = brackets.h

CFLAGS=-fmessage-length=0

brackets: $(SOURCES) $(HEADERS)
	g++ $(CFLAGS) -o brackets $(SOURCES)

debug: $(SOURCES) $(HEADERS)
	g++ $(CFLAGS) -g -o brackets $(SOURCES)

clean:
	rm -f *.o brackets
	
all: brackets
