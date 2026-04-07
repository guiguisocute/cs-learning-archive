CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
BUILD_DIR := build
TARGET := $(BUILD_DIR)/bitmap_lab
SRCS := src/main.c src/bitmap_lab.c

.PHONY: all clean run test scaffold-check

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRCS) include/bitmap_lab.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

scaffold-check: $(TARGET)
	python3 tests/check_reference_output.py

test: scaffold-check

clean:
	rm -rf $(BUILD_DIR)
