#makefile
CC = g++
CFLAGS = -Wall
DEPS = 
OBJ = main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

infixtopostfix: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o infixtopostfix
