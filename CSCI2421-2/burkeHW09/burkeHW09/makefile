#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = Contact.h Menu.h MenuFunctions.h BSTree.h
OBJ = Contact.o Menu.o MenuFunctions.o BSTree.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeFP: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeFP core
