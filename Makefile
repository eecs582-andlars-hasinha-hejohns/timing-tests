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
.PHONY: all clean test
