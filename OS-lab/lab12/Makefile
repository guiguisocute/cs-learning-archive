CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror -Iinclude

REFERENCE_SRCS := src/reference_main.c src/mem_model.c src/io_view.c
STUDENT_SRCS := src/main.c src/mem_model.c src/io_view.c

.PHONY: all reference student clean

all: reference

reference: bin/reference_lab

student: bin/student_lab

bin/reference_lab: $(REFERENCE_SRCS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(REFERENCE_SRCS) -o $@

bin/student_lab: $(STUDENT_SRCS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(STUDENT_SRCS) -o $@

clean:
	rm -rf bin
