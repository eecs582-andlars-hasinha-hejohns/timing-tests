all: A B
A: A.c
	$(CC) $(CFLAGS) -o $@ $^
B: B.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	-find . -type f -executable -delete
test: all
	perl ./test.packed.pl # so root doesn't have to `cpan IPC::Run`
.PHONY: all clean test
