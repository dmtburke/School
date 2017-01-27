#makefile
CC = g++
CFLAGS = -Wall -std=c++11
DEPS = ErrorContext.h custom_iterator.h less_functor.h TemplateTests.h
OBJ = ErrorContext.o main.o TemplateTests.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ucd-csci2312-pa5: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o ucd-csci2312-pa5
