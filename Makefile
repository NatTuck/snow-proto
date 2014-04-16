
BASE    := $(shell readlink -f .)

LD      := clang++
CC      := clang
CFLAGS  := -g -Iinclude -Isrc/parser -Ivendor/libdrip/include `llvm-config --cflags`
LIBS    := -ldrip -lreadline -lgc `llvm-config --libs core analysis executionengine jit interpreter native`
LDFLAGS := -Llib `llvm-config --ldflags`

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

bin/parse: $(OBJS) lib/libdrip.so 
	$(LD) $(CFLAGS) -o bin/parse $(OBJS) $(LDFLAGS) $(LIBS)

bin/snow: $(OBJS) lib/libdrip.so
	$(LD) $(CFLAGS) -o bin/snow $(OBJS) $(LDFLAGS) $(LIBS)

%.o : %.c $(HDRS)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: all update clean $(PHONY)

update:
	git submodule init
	git submodule update

clean:
	rm -f $(BINS) $(OBJS) $(DEBRIS)
