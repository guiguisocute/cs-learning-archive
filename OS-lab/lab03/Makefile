CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Werror -Iinclude
TARGET := sjf_lab

SRC := src/main.c src/sjf_lab.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC) include/sjf_lab.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
