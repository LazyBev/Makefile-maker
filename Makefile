# Maded with maker.c
CC=gcc
CCFLAGS=-Wall -Wextra
IN=maker.c
OUT=maker
SRC=src
BUILD=build

fresh:
	mkdir -p $(BUILD)
	mkdir -p $(SRC) && touch $(SRC)/$(IN)
start:
	mkdir -p $(BUILD)
	mkdir -p $(SRC) && mv $(IN) $(SRC)
all:
	$(CC) -o $(BUILD)/$(OUT) $(SRC)/$(IN) $(CCFLAGS)
run:
	./$(BUILD)/$(OUT)
clean:
	mv $(SRC)/* .
	rm -rf $(BUILD) && rm -rf $(SRC)
wipe:
	rm -rf $(BUILD) && rm -rf $(SRC)

