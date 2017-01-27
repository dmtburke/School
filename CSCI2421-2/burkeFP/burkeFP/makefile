#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = Contact.h Menu.h TreeFunc.h MenuFunctions.h
OBJ = Contact.o Menu.o TreeFunc.o MenuFunctions.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

burkeFP: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o burkeFP
