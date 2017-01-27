#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = ErrorContext.h Advantage.h Agent.h AggressiveAgentStrategy.h DefaultAgentStrategy.h Exceptions.h Food.h Game.h Gaming.h GamingTests.h Piece.h Resource.h Simple.h Strategic.h Strategy.h
OBJ = ErrorContext.o  Advantage.o Agent.o AggressiveAgentStrategy.o DefaultAgentStrategy.o Exceptions.o Food.o Game.o GamingTests.o Piece.o Resource.o Simple.o Strategic.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ucd-csci2312-pa4: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o ucd-csci2312-pa4
