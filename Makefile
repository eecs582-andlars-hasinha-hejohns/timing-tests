CFLAGS = -O3 -I$(shell pwd)
export
all:
	$(MAKE) -C getcpu/
	$(MAKE) -C getpid/
clean:
	$(MAKE) -C getcpu clean
	$(MAKE) -C getpid clean
.PHONY: all clean
