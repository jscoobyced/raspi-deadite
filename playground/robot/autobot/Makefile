CC=gcc
CFLAGS=-Wall -pthread
LIBS=../../servo/libs
FACEMOVE=facemove

CPP=g++
CFLAGSPP=$(shell pkg-config --cflags opencv)
LIBSPP=$(shell pkg-config --libs opencv)
LIBFACE=face
EXEC=centerface

INCLUDE=../libs
CONTROLLER=controller
UART=uart
BIN=../bin


defaults: make
all: init libs makelibs make

makelibs: $(EXEC).cpp
	$(CC) $(CFLAGS) -c ${FACEMOVE}.c -fPIC -pthread -o $(BIN)/shared/${FACEMOVE}.o
	$(CC) -L $(CFLAGS) -shared -Wl,-soname,lib${FACEMOVE}.so,-rpath=. -o $(BIN)/shared/lib${FACEMOVE}.so $(BIN)/shared/${FACEMOVE}.o
	$(CPP) -L $(CFLAGSPP) $(LIBSPP) -c ${LIBFACE}.cpp -fPIC -pthread -o $(BIN)/shared/${LIBFACE}.o
	$(CPP) -L $(CFLAGSPP) $(LIBSPP) -shared -Wl,-soname,lib${LIBFACE}.so,-rpath=. -o $(BIN)/shared/lib${LIBFACE}.so $(BIN)/shared/${LIBFACE}.o

make: $(EXEC).cpp
	$(CPP) -L $(BIN)/shared $(CFLAGSPP) $(LIBSPP) -l$(FACEMOVE) -l$(LIBFACE) -l$(UART) -l$(CONTROLLER) -o $(BIN)/$(EXEC) $(EXEC).cpp

init:
	mkdir -p $(BIN)/shared

clean:
	rm -Rf $(BIN)

libs:
	cd $(LIBS) && $(MAKE)
	cp $(LIBS)/$(BIN)/shared/*.so $(BIN)/shared/