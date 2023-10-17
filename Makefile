CFLAGS = -O3 -I$(shell pwd)
export
TESTS := $(file < TESTS)

define newline


endef

all:
	$(foreach test,$(TESTS),$(MAKE) -C $(test)/ $(newline))
clean:
	$(foreach test,$(TESTS),$(MAKE) -C $(test)/ clean $(newline))
test: all
	$(foreach test,$(TESTS),$(MAKE) -C $(test)/ test $(newline))
test-silent:
	(cat /proc/cpuinfo | grep 'model name'; \
	cat /sys/devices/system/cpu/vulnerabilities/meltdown; \
	$(MAKE) -s test) | tee results/$(file < /proc/sys/kernel/random/uuid)
.PHONY: all clean test test-silent
