CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
TARGET := bitmap_lab
SRCS := src/main.c src/bitmap_lab.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRCS) include/bitmap_lab.h
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
