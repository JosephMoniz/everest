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

DEPS  = $(SSLDIR)/libcrypto.a
DEPS += $(SSLDIR)/libssl.a
DEPS += $(HTTPDIR)/libhttp_parser.a

INCLUDES  = -I$(SRCDIR)
INCLUDES += -I$(TESTDIR)
INCLUDES += -I$(SSLDIR)/include

$(BUILDDIR)/everest: $(DEPS) $(BUILDDIR)/main.o
	$(CXX) $(CFLAGS_FAST) -o $@ $^

$(BUILDDIR)/%.o: $(TESTDIR)/%.cc
	mkdir -p `dirname $@`
	$(CXX) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

$(SSLDIR)/README:
	git submodule update --init $(SSLDIR)

$(SSLDIR)/Makefile: $(SSLDIR)/README
	cd $(SSLDIR); ./config no-shared

$(SSLDIR)/include/openssl/opensslconf.h: $(SSLDIR)/Makefile
	$(MAKE) -C $(SSLDIR)

$(SSLDIR)/libcrypto.a: $(SSLDIR)/include/openssl/opensslconf.h

$(SSLDIR)/libssl.a: $(SSLDIR)/include/openssl/opensslconf.h

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
