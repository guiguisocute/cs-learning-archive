CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Iinclude
TARGET = build/device_manager
SRCS = src/main.c src/device_manager.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) include/device_manager.h
	mkdir -p build
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -rf build
