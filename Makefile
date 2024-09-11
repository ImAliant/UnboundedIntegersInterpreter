CC := gcc
CFLAGS := -Wall
READLINE := -lreadline
SRC := src
MAIN := $(SRC)/main
TEST := $(SRC)/test

INTERPRETER := $(MAIN)/interpreter.c
UNBOUNDED_INT := $(MAIN)/unbounded_int.c
TEST_UNBOUNDED := $(TEST)/test_unbounded.c

all: interpreter test

interpreter: $(UNBOUNDED_INT) $(INTERPRETER)
	$(CC) $(CFLAGS) -o $@ $^ $(READLINE)

test: $(UNBOUNDED_INT) $(TEST_UNBOUNDED)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f interpreter test