CC = gcc
BIN = build/friday13.so
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
FILES = $(shell find src -type f -iname '*.c')

all: run

.PHONY: build
build:
	$(CC) $(FILES) $(CFLAGS) -o $(BIN) 

.PHONY: run
run: build
	./build/friday13.so

.PHONY: lib
lib: 
	$(CC) $(FILES) $(CFLAGS) -fPIC -o $(BIN) 

# == VALGRIND == 

.PHONY: leak-check
leak-check: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./build/friday13.so src/main.c

# == LINTING == 

TARGETS = $(shell find src -type f -iname '*.h' -or -iname '*.c')

.PHONY: lint
lint: $(OBJ)
	@clang-format -style=file -i $(TARGETS)
	@echo "== REFORMATTED SUCCESSFULLY =="

