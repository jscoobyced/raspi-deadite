CC=g++
CFLAGS=$(shell pkg-config --cflags opencv)
LIBS=$(shell pkg-config --libs opencv)
EXEC=facedetect
BIN=../bin

defaults: init make

make: $(EXEC).cpp
	$(CC) $(CFLAGS) -L $(LIBS) -o $(BIN)/$(EXEC) $(EXEC).cpp

init:
	mkdir -p $(BIN)
