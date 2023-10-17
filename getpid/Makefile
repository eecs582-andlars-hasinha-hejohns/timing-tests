all: getpid-implicit-syscall getpid-explicit-syscall
getpid-implicit-syscall: getpid.c
	$(CC) $(CFLAGS) -o $@ $^
getpid-explicit-syscall: getpid.syscall.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	-find . -type f -executable -delete
test: all
	find . -type f -executable -exec {} \;
.PHONY: all clean test
