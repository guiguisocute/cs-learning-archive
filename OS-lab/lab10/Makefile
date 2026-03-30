CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS :=
TARGET := bin/lab10

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

.PHONY: all clean run test

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

test: $(TARGET)
	@echo "当前 src/ 是教学脚手架，未补全 TODO 前不提供自动样例比对。"
	@echo "已验证的参考输出请查看 docs/case_reference_output.md"

clean:
	rm -rf bin obj
