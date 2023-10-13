all: A B
A: A.c
	$(CC) $(CFLAGS) -o $@ $^
B: B.c
	$(CC) $(CFLAGS) -o $@ $^
test: A B
	sudo ./test.packed.pl # so root doesn't have to `cpan IPC::Run`
clean:
	-rm A B
.PHONY: all clean test
