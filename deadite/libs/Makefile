CC=gcc
CFLAGS=-Wall -pthread
CONTROLLER=controller
UART=uart
SERVER=server
CLIENT=client
L298N=l298n
BLUETOOTH=bt
WIRINGPI=wiringPi
BIN=../bin

default: make

others: ${BLUETOOTH}.c ${SERVER}.c ${CLIENT}.c
	$(CC) $(CFLAGS) -c ${BLUETOOTH}.c -fPIC -pthread -o $(BIN)/shared/${BLUETOOTH}.o
	$(CC) $(CFLAGS) -shared -L. -L$(BIN)/shared -lbluetooth -Wl,-soname,lib${BLUETOOTH}.so,-rpath=. -o $(BIN)/shared/lib${BLUETOOTH}.so $(BIN)/shared/${BLUETOOTH}.o
	$(CC) $(CFLAGS) -c ${SERVER}.c -fPIC -pthread -o $(BIN)/shared/${SERVER}.o
	$(CC) $(CFLAGS) -shared -L. -Wl,-soname,lib${SERVER}.so,-rpath=. -o $(BIN)/shared/lib${SERVER}.so $(BIN)/shared/${SERVER}.o
	$(CC) $(CFLAGS) -c ${CLIENT}.c -fPIC -pthread -o $(BIN)/shared/${CLIENT}.o
	$(CC) $(CFLAGS) -shared -L. -Wl,-soname,lib${CLIENT}.so,-rpath=. -o $(BIN)/shared/lib${CLIENT}.so $(BIN)/shared/${CLIENT}.o

make: ${CONTROLLER}.c ${UART}.c ${SERVER}.c ${CLIENT}.c ${L298N}.c
	$(CC) $(CFLAGS) -c ${UART}.c -fPIC -pthread -o $(BIN)/shared/${UART}.o
	$(CC) $(CFLAGS) -shared -L. -Wl,-soname,lib${UART}.so,-rpath=. -o $(BIN)/shared/lib${UART}.so $(BIN)/shared/${UART}.o
	$(CC) $(CFLAGS) -c ${CONTROLLER}.c -fPIC -pthread -o $(BIN)/shared/${CONTROLLER}.o
	$(CC) $(CFLAGS) -shared -L. -L$(BIN)/shared -l${UART} -Wl,-soname,lib${CONTROLLER}.so,-rpath=. -o $(BIN)/shared/lib${CONTROLLER}.so $(BIN)/shared/${CONTROLLER}.o
	gcc $(CFLAGS) -c ${L298N}.c -fPIC -pthread -o $(BIN)/shared/${L298N}.o
	gcc $(CFLAGS) -shared -L. -L$(BIN)/shared -l$(WIRINGPI) -Wl,-soname,lib${L298N}.so,-rpath=. -o $(BIN)/shared/lib${L298N}.so $(BIN)/shared/${L298N}.o
