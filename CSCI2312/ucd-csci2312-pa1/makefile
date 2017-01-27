#makefile
CC = g++
CFLAGS = -Wall
DEPS = ErrorContext.h Point.h PointTests.h
OBJ = ErrorContext.o main.o PointTests.o Point.o area.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ucd-csci2312-pa1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o ucd-csci2312-pa1
