#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = ArrayBag.h SetFunctions.h
OBJ = ArrayBag.o SetFunctions.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW02: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW02 core
