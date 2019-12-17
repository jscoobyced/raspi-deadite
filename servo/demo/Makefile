CC=gcc 
CFLAGS=-Wall -pthread
INCLUDE=../libs
CONTROLLER=controller
UART=uart
EXEC=demo
BIN=../bin

defaults: make

make: $(EXEC).c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $(EXEC).c -o $(BIN)/$(EXEC).o
	$(CC) $(CFLAGS) -o $(BIN)/$(EXEC) $(BIN)/$(EXEC).o -L$(BIN)/shared -l${CONTROLLER} -l${UART}
