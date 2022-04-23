CC=gcc
DEPS = unbounded_int.h
OBJ = unbounded_int.o calc_unbounded_int.o
OBJ_TEST = unbounded_int.o test_unbounded_int.o

ifeq ($(OS), Windows_NT)
	cmd = del
else
	cmd = rm
endif

%.o: %.c %(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prog : $(OBJ)
	$(CC) -o $@ -Wall -g -pedantic $^ $(CFLAGS) 

test : $(OBJ_TEST)
	$(CC) -o $@ -Wall -g -pedantic $^ $(CFLAGS)

clean :
	@echo "clean project"
	-$(cmd) prog.exe *.o
	-$(cmd) test.exe *.o
	@echo "clean completed"
.PHONY: clean