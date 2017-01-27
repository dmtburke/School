#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = Recursion.h
OBJ = Recursion.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW03: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW03 core
