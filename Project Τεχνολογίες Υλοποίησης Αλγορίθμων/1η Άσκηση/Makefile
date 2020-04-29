name = Ergasia_1
src = $(wildcard *.cpp)
obj = $(src:/c=.o)

CC = g++
CFLAGS = -std=c++0x -O3
LIBFLAGS = -lleda -lm

Leda = '/usr/local/LEDA/incl'
LedaLibs = '/usr/local/LEDA'

all: $(name)
$(name): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ -I$(Leda) -L$(LedaLibs) $(LIBFLAGS)
	
run:
	./$(name)
	
clean:
	rm -f $(name)