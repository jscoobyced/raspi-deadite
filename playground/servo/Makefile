BIN=./bin

default: make

init:
	mkdir -p $(BIN)/shared

make: clean init subsystems

subsystems:
	$(MAKE) -C libs
	$(MAKE) -C demo
	$(MAKE) -C head

clean:
	rm -Rf $(BIN)