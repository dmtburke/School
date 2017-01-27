#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = dictionary.h filecheck.h
OBJ = dictionary.o filecheck.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW10: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW10 core
