
PARSER_SRCS := $(sort $(wildcard src/parser/*.c) src/parser/grammar.c)
PARSER_OBJS := $(PARSER_SRCS:.c=.o)

HDRS   += src/parser/grammar.h
OBJS   += $(PARSER_OBJS)
DEBRIS += src/parser/grammar.c src/parser/grammar.h src/parser/grammar.out

src/parser/grammar.c: bin/lemon src/parser/grammar.y
	(cd src/parser && $(BASE)/bin/lemon T=$(BASE)/tools/lemon/lempar.c grammar.y)

src/parser/grammar.h: src/parser/grammar.c
	touch src/parser/grammar.h

