# Variables
L = ../libcs50
M = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I $M -I $L
PROG = indexer
PROG2= indextest
OBJS = indexer.o
OBJS2= indextest.o
LLIBS = $M/common.a $L/libcs50-given.a

# Rules
all: $(PROG) $(PROG2)

# make -C ../common

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

$(PROG2): $(OBJS2) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

# Phony Targets
.PHONY: test clean

test:
	./testing.sh

clean:
	rm -f core
	rm -f $(PROG) *~ *.o
