
BASE    := $(shell readlink -f .)

CC      := clang
CFLAGS  := -g -Iinclude/snow -Isrc/parser
LIBS    := -lreadline -lgc
LDFLAGS := 

PHONY   := 
OBJS    :=
BINS    := bin/parse

HDRS    := $(wildcard include/snow/*.h)

all: bin/parse

include tools/lemon/rules.mk

include src/parser/rules.mk
include src/codegen/rules.mk

bin/parse: $(OBJS) 
	$(CC) $(CFLAGS) -o bin/parse $(OBJS) $(LDFLAGS) $(LIBS)

%.o : %.c $(HDRS)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: all clean $(PHONY)

parse: parse.c token.c grammar.c grammar.h
	$(CC) -o parse parse.c token.c grammar.c $(LIBS)

grammar.c: grammar.y lemon
	./lemon -c grammar.y

grammar.h: grammar.c
	touch grammar.h

clean:
	rm -f $(BINS) $(OBJS) $(DEBRIS)
