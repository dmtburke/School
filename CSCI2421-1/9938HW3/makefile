#makefile
CC = g++
CFLAGS = -Wall
DEPS = format.h
OBJ = format.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

format: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o format
