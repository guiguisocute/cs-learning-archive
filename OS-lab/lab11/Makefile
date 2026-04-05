CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Werror -Iinclude
BUILD_DIR := build
TARGET := $(BUILD_DIR)/paging_lab
REFERENCE_TARGET := $(BUILD_DIR)/paging_lab_reference
SRC := src/main.c
REFERENCE_SRC := tests/reference_paging.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

$(REFERENCE_TARGET): $(REFERENCE_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(REFERENCE_SRC) -o $(REFERENCE_TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: $(TARGET) $(REFERENCE_TARGET)
	sh tests/test_cases.sh

clean:
	rm -rf $(BUILD_DIR)
