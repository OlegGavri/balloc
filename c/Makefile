
all: balloc_test

CFLAGS+= -DTEST -DBLOCKS_NUM=16 -g -O0

balloc_test: balloc.c balloc_test.c

clean:
	rm -f balloc_test *.o

.PHONY: clean
