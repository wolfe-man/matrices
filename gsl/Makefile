# this target will complile all f the files
CC=gcc

CFLAGS= -c -Wall

PROJECT= gsl

all: $(PROJECT)

$(PROJECT): main.o
	$(CC) -L/Users/cwolfe/gsl/lib main.o -o $(PROJECT) -lgsl -lgslcblas -lm

main.o: main.cpp
	$(CC) $(CFLAGS) -I/Users/cwolfe/gsl/include main.cpp

# function1.o: function1.cpp
# $(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *o $(PROJECT)
