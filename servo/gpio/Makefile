HEADERS = servo.h
CC=gcc 
CFLAGS=-Wall -Wall -pthread
BIN=./bin

default: clean make

demo: demo.c $(HEADERS)
	$(CC) $(CFLAGS) -c demo.c -o $(BIN)/demo.o
	$(CC) $(CFLAGS) -o $(BIN)/demo $(BIN)/demo.o -L$(BIN)/shared -lservo -lpigpio

deps: servo.c $(HEADERS)
	$(CC) $(CFLAGS) -c servo.c -fPIC -pthread -lpigpio -o $(BIN)/shared/servo.o
	$(CC) $(CFLAGS) -shared -L. -Wl,-soname,libservo.so,-rpath=. -o $(BIN)/shared/libservo.so $(BIN)/shared/servo.o

init:
	mkdir -p $(BIN)/shared

make: init deps demo

clean:
	rm -Rf ./bin

run:
	LD_LIBRARY_PATH=$(BIN)/shared $(BIN)/demo
