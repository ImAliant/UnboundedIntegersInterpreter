CC := gcc
CFLAGS := -Wall
SRC := src
MAIN := $(SRC)/main
TEST := $(SRC)/test

UNBOUNDED_INT := $(MAIN)/unbounded_int.c
TEST_UNBOUNDED := $(TEST)/test_unbounded.c

all: test # need to add interpreter rule

test: $(UNBOUNDED_INT) $(TEST_UNBOUNDED)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f test