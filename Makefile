BUILDDIR=build
SRCDIR=src
TESTDIR=tests
SSLDIR=deps/openssl
HTTPDIR=deps/http-parser

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

DEPS = $(SSLDIR)/libcrypto.a       \
       $(SSLDIR)/libssl.a          \
       $(HTTPDIR)/libhttp_parser.a

INCLUDES = -I$(SRCDIR) -I$(TESTDIR) -I$(SSLDIR)/include

$(BUILDDIR)/everest: $(BUILDDIR)/main.o $(DEPS)
	$(CXX) $(CFLAGS_DEBUG) -o $@ $^

$(BUILDDIR)/%.o: $(TESTDIR)/%.cc
	mkdir -p `dirname $@`
	$(CXX) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

$(SSLDIR)/README:
	git submodule update --init $(SSLDIR)

$(SSLDIR)/Makefile: $(SSLDIR)/README
	cd $(SSLDIR); ./config no-shared

$(SSLDIR)/libcrypto.a: $(SSLDIR)/Makefile
	$(MAKE) -C $(SSLDIR)

$(HTTPDIR)/Makefile:
	git submodule update --init $(HTTPDIR)

$(HTTPDIR)/libhttp_parser.a: $(HTTPDIR)/Makefile
	$(MAKE) package -C $(HTTPDIR)

test:
	$(MAKE) clean-test
	$(MAKE)
	cp -R ./tests/fixtures ./build
	./build/everest

clean-test:
	rm -rf build

clean: clean-test
	$(MAKE) -C $(SSLDIR) clean
	$(MAKE) -C $(HTTPDIR) clean

.PHONY: dep clean test
