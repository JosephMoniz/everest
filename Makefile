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
CFLAGS_TEST = $(CFLAGS) -O0
CFLAGS_DEBUG = $(CFLAGS) -O0 -g

INCLUDES = -I$(SRCDIR)

$(BUILDDIR)/everest: $(BUILDDIR)/main.o
	$(CXX) $(CFLAGS_DEBUG) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	mkdir -p `dirname $@`
	$(CXX) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

test:
	$(MAKE) clean
	$(MAKE)
	./build/everest

dep:
	$(CXX) -MM $(SRCDIR)/*.cc $(INCLUDES)

clean:
	rm -rf build

.PHONY: dep clean test
