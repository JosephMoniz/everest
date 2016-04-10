BUILDDIR=build
SRCDIR=src
TESTDIR=tests

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wno-return-type
CFLAGS += -Wno-unknown-pragmas
CFLAGS += --std=c++14

CFLAGS_FAST = $(CFLAGS) -O3
CFLAGS_TEST = $(CFLAGS) -O0
CFLAGS_DEBUG = $(CFLAGS) -O0 -g

INCLUDES = -I$(SRCDIR) -I$(TESTDIR)

$(BUILDDIR)/everest: $(BUILDDIR)/main.o
	$(CXX) $(CFLAGS_DEBUG) -o $@ $^

$(BUILDDIR)/%.o: $(TESTDIR)/%.cc
	mkdir -p `dirname $@`
	$(CXX) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

test:
	$(MAKE) clean
	$(MAKE)
	cp -R ./tests/fixtures ./build
	./build/everest

clean:
	rm -rf build

.PHONY: dep clean test
