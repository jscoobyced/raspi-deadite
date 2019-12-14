HEADERS=controller.h
CC=gcc 
CFLAGS=-Wall -Wall -pthread
DEPS=controller
BIN=./bin

default: clean make

demo: demo.c $(HEADERS)
	$(CC) $(CFLAGS) -c demo.c -o $(BIN)/demo.o
	$(CC) $(CFLAGS) -o $(BIN)/demo $(BIN)/demo.o -L$(BIN)/shared -l${DEPS}

deps: ${DEPS}.c $(HEADERS)
	$(CC) $(CFLAGS) -c ${DEPS}.c -fPIC -pthread -o $(BIN)/shared/${DEPS}.o
	$(CC) $(CFLAGS) -shared -L. -Wl,-soname,lib${DEPS}.so,-rpath=. -o $(BIN)/shared/lib${DEPS}.so $(BIN)/shared/${DEPS}.o

init:
	mkdir -p $(BIN)/shared

make: init deps demo

clean:
	rm -Rf ./bin

run:
	LD_LIBRARY_PATH=$(BIN)/shared $(BIN)/demo
