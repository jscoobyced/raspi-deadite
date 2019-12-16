HEADERS=controller.h
CC=gcc 
CFLAGS=-Wall -Wall -pthread
CONTROLLER=controller
UART=uart
BIN=./bin

default: clean make

init:
	mkdir -p $(BIN)/shared

deps: ${CONTROLLER}.c ${UART}.c $(HEADERS)
	$(CC) $(CFLAGS) -c ${UART}.c -fPIC -pthread -o $(BIN)/shared/${UART}.o
	$(CC) $(CFLAGS) -shared -L. -Wl,-soname,lib${UART}.so,-rpath=. -o $(BIN)/shared/lib${UART}.so $(BIN)/shared/${UART}.o
	$(CC) $(CFLAGS) -c ${CONTROLLER}.c -fPIC -pthread -o $(BIN)/shared/${CONTROLLER}.o
	$(CC) $(CFLAGS) -shared -L. -L$(BIN)/shared -l${UART} -Wl,-soname,lib${CONTROLLER}.so,-rpath=. -o $(BIN)/shared/lib${CONTROLLER}.so $(BIN)/shared/${CONTROLLER}.o

demo: demo.c $(HEADERS)
	$(CC) $(CFLAGS) -c demo.c -o $(BIN)/demo.o
	$(CC) $(CFLAGS) -o $(BIN)/demo $(BIN)/demo.o -L$(BIN)/shared -l${CONTROLLER} -l${UART}

make: init deps demo

clean:
	rm -Rf ./bin

run:
	LD_LIBRARY_PATH=$(BIN)/shared $(BIN)/demo "/dev/serial0" 0
