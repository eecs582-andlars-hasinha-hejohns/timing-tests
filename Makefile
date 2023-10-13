CFLAGS = -O3 -I$(shell pwd)
export
all:
	$(MAKE) -C getcpu/
clean:
	$(MAKE) -C getcpu clean
.PHONY: all clean
