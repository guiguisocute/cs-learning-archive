CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude

TARGET := lab09
REFERENCE_TARGET := lab09_reference

.PHONY: all clean run case sample reference reference-run reference-case

all: $(TARGET)

$(TARGET): src/main.c include/paging_lab.h
	$(CC) $(CFLAGS) src/main.c -o $(TARGET)

$(REFERENCE_TARGET): docs/reference_solution.c include/paging_lab.h
	$(CC) $(CFLAGS) docs/reference_solution.c -o $(REFERENCE_TARGET)

run: $(TARGET)
	./$(TARGET)

case: $(TARGET)
	./$(TARGET) < data/sample_case_01.txt

sample: case

reference: $(REFERENCE_TARGET)

reference-run: $(REFERENCE_TARGET)
	./$(REFERENCE_TARGET)

reference-case: $(REFERENCE_TARGET)
	./$(REFERENCE_TARGET) < data/sample_case_01.txt

clean:
	rm -f $(TARGET) $(REFERENCE_TARGET)
