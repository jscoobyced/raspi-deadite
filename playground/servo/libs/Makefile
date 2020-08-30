CC=arm-linux-gnueabihf-gcc 
CFLAGS=-Wall -pthread
CONTROLLER=controller
UART=uart
BIN=../bin

default: make

make: ${CONTROLLER}.c ${UART}.c
	$(CC) $(CFLAGS) -c ${UART}.c -fPIC -pthread -o $(BIN)/shared/${UART}.o
	$(CC) $(CFLAGS) -shared -L. -Wl,-soname,lib${UART}.so,-rpath=. -o $(BIN)/shared/lib${UART}.so $(BIN)/shared/${UART}.o
	$(CC) $(CFLAGS) -c ${CONTROLLER}.c -fPIC -pthread -o $(BIN)/shared/${CONTROLLER}.o
	$(CC) $(CFLAGS) -shared -L. -L$(BIN)/shared -l${UART} -Wl,-soname,lib${CONTROLLER}.so,-rpath=. -o $(BIN)/shared/lib${CONTROLLER}.so $(BIN)/shared/${CONTROLLER}.o
