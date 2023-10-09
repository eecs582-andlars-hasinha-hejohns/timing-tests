all: getcpu getcpu_ getcpu__
getcpu: getcpu.c
	$(CC) -o $@ $^ -O3
getcpu_: getcpu.vdso.c
	$(CC) -o $@ $^ -O3
getcpu__: getcpu.syscall.c
	$(CC) -o $@ $^ -O3
clean:
	-rm getcpu getcpu_ getcpu__
.PHONY: all clean
