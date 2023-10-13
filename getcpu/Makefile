all: getcpu-implicit-vdso getcpu-explicit-vdso getcpu-syscall
getcpu-implicit-vdso: getcpu.c
	$(CC) -o $@ $^ -O3
getcpu-explicit-vdso: getcpu.vdso.c
	$(CC) -o $@ $^ -O3
getcpu-syscall: getcpu.syscall.c
	$(CC) -o $@ $^ -O3
clean:
	-rm getcpu-*
.PHONY: all clean
