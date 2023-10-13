all: getcpu-implicit-vdso getcpu-explicit-vdso getcpu-syscall
getcpu-implicit-vdso: getcpu.c
	$(CC) $(CFLAGS) -o $@ $^
getcpu-explicit-vdso: getcpu.vdso.c
	$(CC) $(CFLAGS) -o $@ $^
getcpu-syscall: getcpu.syscall.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	-rm getcpu-*
.PHONY: all clean
