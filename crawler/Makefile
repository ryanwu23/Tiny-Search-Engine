# Variables
L = ../libcs50
M = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I $M -I $L
PROG = crawler
OBJS = crawler.o
LLIBS = $L/libcs50-given.a $M/common.a 

# Rules
all: $(PROG)

# make -C ../common

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

# Phony Targets
.PHONY: test clean

test:
	./testing.sh

clean:
	rm -f core
	rm -f $(PROG) *~ *.o
