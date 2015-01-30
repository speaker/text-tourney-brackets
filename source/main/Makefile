# First pass ultra simple Makefile

SOURCES = main.cpp brackets.cpp team.cpp roster.cpp match.cpp
HEADERS = brackets.h

CFLAGS=-fmessage-length=0

brackets: $(SOURCES) $(HEADERS)
	g++ $(DEBUG) $(CFLAGS) -o brackets $(SOURCES)

clean:
	rm -f *.o brackets
	
all: brackets
