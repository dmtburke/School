#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = MyVector.h
OBJ = MyVector.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW04: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW04 core
