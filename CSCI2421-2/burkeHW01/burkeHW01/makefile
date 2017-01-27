#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = game.h
OBJ = game.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW01: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW01
