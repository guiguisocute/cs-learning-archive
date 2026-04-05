CC := cc
CFLAGS := -std=c11 -Wall -Wextra -pedantic -Iinclude
BUILD_DIR := build
TARGET := $(BUILD_DIR)/disk_scheduler
SOURCES := \
	src/main.c \
	src/app.c \
	src/io.c \
	src/scheduler_common.c \
	src/scheduler_fcfs.c \
	src/scheduler_sstf.c \
	src/scheduler_scan.c

.PHONY: all run test scaffold-check plot-example clean

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SOURCES) include/*.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

run: $(TARGET)
	./$(TARGET)

scaffold-check: $(TARGET)
	python3 tests/check_reference_output.py
	python3 scripts/check_readme.py
	python3 scripts/check_cases.py

test: scaffold-check

plot-example:
	python3 scripts/plot_schedule.py --title SSTF --sequence 53 65 67 37 14 98 122 124 183 --output $(BUILD_DIR)/sstf.svg

clean:
	rm -rf $(BUILD_DIR)
