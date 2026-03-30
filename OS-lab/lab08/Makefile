CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS :=
TARGET := bin/lab08

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ) | bin
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

obj:
	mkdir -p obj

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf bin obj
