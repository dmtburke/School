#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = StringOfNodes.h
OBJ = StringOfNodes.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeHW05: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeHW05 core
