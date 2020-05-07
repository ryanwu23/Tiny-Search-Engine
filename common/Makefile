# Variables
L = ../libcs50

CC = gcc
GFLAGS = -Wall -pedantic -std=c11 -ggdb -I $L
OBJS = pagedir.o
LIB = common.a
LLIBS = $L/libcs50-given.a

# Rules
$(LIB): $(OBJS) $(LLIBS)
	ar cr $(LIB) $^

# Phony tagets
.PHONY: clean

clean:
	rm -f core
	rm -f $(LIB) *~ *.o
