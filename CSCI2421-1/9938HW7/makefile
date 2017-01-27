#makefile
CC = g++
CFLAGS = -Wall
DEPS = 
OBJ = main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

coins: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o coins
