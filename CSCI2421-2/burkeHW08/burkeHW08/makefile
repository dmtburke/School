#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = BSTree.h
OBJ = BSTree.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW08: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW08 core
