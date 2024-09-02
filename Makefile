CC = gcc
BIN = build/friday13
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
FILES = $(shell find src -type f -iname '*.c')
DEBUG = 1

ifeq ($(DEBUG),1)
	CFLAGS += -DDEBUG
endif

all: run

.PHONY: build
build:
	$(CC) $(FILES) $(CFLAGS) -o $(BIN)

.PHONY: run
run: build
	./build/friday13

.PHONY: lib
lib: 
	$(CC) $(FILES) $(CFLAGS) -fPIC -o $(BIN).so 

# == VALGRIND == 

.PHONY: leak-check
leak-check: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./build/friday13 src/main.c

# == LINTING == 

TARGETS = $(shell find src -type f -iname '*.h' -or -iname '*.c')

.PHONY: lint
lint: $(OBJ)
	@clang-format -style=file -i $(TARGETS)
	@echo "== REFORMATTED SUCCESSFULLY =="

