#makefile
CC = g++
CFLAGS = -Wall
DEPS = node1.h
OBJ = node1.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

nodeo: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o nodeo
