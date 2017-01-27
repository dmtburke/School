#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = DictEntry.h dictionary.h
OBJ = dictionary.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW06: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW06 core
