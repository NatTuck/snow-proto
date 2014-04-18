
BASE    := $(shell readlink -f .)

LD      := g++
CC      := gcc
#CFLAGS  := -g -O0 -std=gnu99 -Iinclude -Isrc/parser -Ivendor/libdrip/include `llvm-config --cflags`
#LIBS    := -ldrip -lreadline -lgc `llvm-config --libs core analysis executionengine jit interpreter native`
#LDFLAGS := -O0 -Llib `llvm-config --ldflags`
CFLAGS  := -O0 -g -std=gnu99 -Iinclude -Isrc/parser -Ivendor/libdrip/include
LIBS    := -ldrip -lreadline -lgc
LDFLAGS := -O0 -Llib

PHONY   := 
OBJS    :=
BINS    := bin/parse bin/snow
DEBRIS  := lib/libdrip.so

HDRS    := $(wildcard include/snow/*.h)

all: $(BINS)

include tools/lemon/rules.mk
include src/parser/rules.mk
include src/codegen/rules.mk

lib/libdrip.so:
	(cd vendor/libdrip && make)
	cp vendor/libdrip/libdrip.so lib/libdrip.so

bin/snow: $(OBJS) lib/libdrip.so
	$(LD) $(CFLAGS) -o bin/snow $(OBJS) $(LDFLAGS) $(LIBS)

%.o : %.c $(HDRS)
	$(CC) -c $(CFLAGS) -o $@ $<

parse: parse.c token.c grammar.c grammar.h
	$(CC) -o parse parse.c token.c grammar.c $(LIBS)

grammar.c: grammar.y lemon
	./lemon -c grammar.y

update:
	git submodule init
	git submodule update

prereqs:
	sudo apt-get install build-essential clang llvm-dev manpages-posix-dev 

clean:
	rm -f $(BINS) $(OBJS) $(DEBRIS)
	(cd vendor/libdrip && make clean)

.PHONY: all clean prereqs $(PHONY)
