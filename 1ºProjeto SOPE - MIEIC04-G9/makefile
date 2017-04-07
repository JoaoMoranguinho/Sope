CC= gcc

#CFLAGS= -std=c11 -Wall -I"headers"
CFLAGS= -std=gnu11 -Wall -I"headers"

#aqui os ficheiros a compilar
FILES=search action signal_handlers
HEADERS=action.h search.h macros.h signal_handlers.h

SOURCES= $(foreach file, $(FILES), src/$(file).c )
OBJECTS= $(foreach file, $(FILES), $(file).o )
HEADERS_PATHS= $(foreach file, $(HEADERS), headers/$(file) )

TEST_LIBS = googletest/bins/gtest_main.a -lpthread
TEST_FLAGS = -I"headers" -I"googletest/include" -std=gnu++11 

find: $(SOURCES) $(HEADERS_PATHS) src/main.c
	$(CC) $(CFLAGS) $(SOURCES)  src/main.c -o sfind

test: $(SOURCES) $(HEADERS_PATHS) src/unit_tests.cpp
	$(CC) $(CFLAGS) $(SOURCES) -c
	g++ $(TEST_FLAGS)  $(OBJECTS) src/unit_tests.cpp  -o test $(TEST_LIBS) 
	rm *.o -f

clean:
	rm find -f
	rm test -f


