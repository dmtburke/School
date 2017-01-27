#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = Contact.h Menu.h AVLTree.h MenuFunctions.h
OBJ = Contact.o Menu.o AVLTree.o MenuFunctions.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

9938FP: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o 9938FP
