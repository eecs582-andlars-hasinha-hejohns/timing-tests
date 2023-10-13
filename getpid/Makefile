all: getpid-implicit-syscall getpid-explicit-syscall
getpid-implicit-syscall: getpid.c
	$(CC) $(CFLAGS) -o $@ $^
getpid-explicit-syscall : getpid.syscall.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	-rm getpid-*
.PHONY: all clean
