#makefile
CC = g++
CFLAGS = -Wall
DEPS = set1.h
OBJ = set1.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sets: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o sets
