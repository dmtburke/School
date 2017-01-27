#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = ErrorContext.h Point.h ClusteringTests.h Cluster.h 
OBJ = ErrorContext.o Point.o ClusteringTests.o Cluster.o main.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ucd-csci2312-pa2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o ucd-csci2312-pa2
