CC=gcc
CFLAGS=-lm
DEPS = TestCode.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

TestCode: TestCode.o main.o
	$(CC) -o $@ $^ $(CFLAGS)

main: main.o
	$(CC) -o $@ main.o $(CFLAGS)
