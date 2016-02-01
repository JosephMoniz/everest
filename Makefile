BUILDDIR=build
SRCDIR=src

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wno-return-type
CFLAGS += -Wno-unknown-pragmas
CFLAGS += --std=c++14

CFLAGS_FAST = $(CFLAGS) -O3
CFLAGS_DEBUG = $(CFLAGS) -O0 -g

INCLUDES = -I$(SRCDIR)

$(BUILDDIR)/traitorous: $(BUILDDIR)/main.o
	$(CC) $(CFLAGS_FAST) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS_FAST) $(INCLUDES) -c $< -o $@

test:
	$(MAKE) clean
	$(MAKE)
	./build/traitorous

dep:
	$(CC) -MM $(SRCDIR)/*.cc $(INCLUDES)

clean:
	rm -rf build

.PHONY: dep clean test
