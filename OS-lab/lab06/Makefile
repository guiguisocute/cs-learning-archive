CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
TARGET := banker_lab
REFERENCE_TARGET := banker_lab_reference

SRC := src/main.c

.PHONY: all clean reference

all: $(TARGET)

$(TARGET): $(SRC) include/banker.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

reference: docs/reference_solution.c include/banker.h
	$(CC) $(CFLAGS) docs/reference_solution.c -o $(REFERENCE_TARGET)

clean:
	rm -f $(TARGET) $(REFERENCE_TARGET)
