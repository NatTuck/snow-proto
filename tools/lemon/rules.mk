
BINS += bin/lemon

bin/lemon: tools/lemon/lemon.c
	$(CC) $(CFLAGS) -o $@ $<

