CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS :=

TARGET := bin/rr_lab
SRC := src/main.c src/rr_lab.c

.PHONY: all clean test check-samples

all: $(TARGET)

$(TARGET): $(SRC) include/rr_lab.h
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

test: $(TARGET)
	@echo "教学脚手架已编译。补完 TODO 后可用 scripts/run_rr.exp 回放样例。"

check-samples: $(TARGET)
	@echo "补完 TODO 后执行: scripts/run_rr.exp --all"

clean:
	rm -rf bin
