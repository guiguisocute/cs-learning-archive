CC := cc
CFLAGS := -std=c11 -Wall -Wextra -pedantic -O2 -Iinclude
TARGET := scheduler_lab
SRC := src/main.c src/fcfs.c src/logger.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
