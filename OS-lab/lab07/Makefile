CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
BUILD_DIR := build
TARGET := $(BUILD_DIR)/fixed_partition_lab
SRCS := src/main.c src/partition.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRCS) include/partition.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
