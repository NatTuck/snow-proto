
BASE    := $(shell readlink -f .)

CC      := clang
CFLAGS  := -g -Iinclude -Isrc/parser -Ivendor/libdrip/include
LIBS    := -ldrip -lreadline -lgc
LDFLAGS := -Llib

PHONY   := 
OBJS    :=
BINS    := bin/parse
DEBRIS  := lib/libdrip.so

HDRS    := $(wildcard include/snow/*.h)

all: bin/parse

include tools/lemon/rules.mk
include src/parser/rules.mk
include src/codegen/rules.mk

lib/libdrip.so:
	(cd vendor/libdrip && make)
	cp vendor/libdrip/libdrip.so lib/libdrip.so

bin/parse: $(OBJS) lib/libdrip.so 
	$(CC) $(CFLAGS) -o bin/parse $(OBJS) $(LDFLAGS) $(LIBS)

%.o : %.c $(HDRS)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: all update clean $(PHONY)

parse: parse.c token.c grammar.c grammar.h
	$(CC) -o parse parse.c token.c grammar.c $(LIBS)

grammar.c: grammar.y lemon
	./lemon -c grammar.y

grammar.h: grammar.c
	touch grammar.h

update:
	git submodule init
	git submodule update

clean:
	rm -f $(BINS) $(OBJS) $(DEBRIS)
