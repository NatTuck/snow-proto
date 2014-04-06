

CC   := clang -g
LIBS := -lreadline -lgc

parse: parse.c token.c grammar.c grammar.h
	$(CC) -o parse parse.c token.c grammar.c $(LIBS)

lemon: lemon.c
	$(CC) -o lemon lemon.c

grammar.c: grammar.y lemon
	./lemon -c grammar.y

grammar.h: grammar.c
	touch grammar.h

clean:
	rm -f *.o parse lemon grammar.c grammar.h grammar.out
