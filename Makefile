CFLAGS = -O3 -I$(shell pwd)
export
all:
	$(MAKE) -C getcpu/
	$(MAKE) -C getpid/
	$(MAKE) -C ctx-switch
clean:
	$(MAKE) -C getcpu clean
	$(MAKE) -C getpid clean
	$(MAKE) -C ctx-switch clean
.PHONY: all clean
