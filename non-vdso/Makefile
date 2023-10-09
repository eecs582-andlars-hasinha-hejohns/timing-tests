all: getpid getpid_
getpid: getpid.c
	$(CC) -o $@ $^ -O3
getpid_ : getpid.syscall.c
	$(CC) -o $@ $^ -O3
clean:
	-rm getpid getpid_
.PHONY: all clean
