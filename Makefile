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

# Main Build Section
#

$(BUILDDIR)/everest: $(DEPS) $(BUILDDIR)/main.o
	$(CXX) $(CFLAGS_DEBUG) -o $@ $^

$(BUILDDIR)/%.o: $(TESTDIR)/%.cc
	mkdir -p `dirname $@`
	$(CXX) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

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

# OpenSSL Build Section
#

$(SSLDIR)/README:
	git submodule update --init $(SSLDIR)

$(SSLDIR)/Makefile: $(SSLDIR)/README
	cd $(SSLDIR); ./Configure darwin64-x86_64-cc no-shared enable-ec_nistp_64_gcc_128 no-comp
	$(MAKE) -C $(SSLDIR) depend
	$(MAKE) -C $(SSLDIR)

$(SSLDIR)/libcrypto.a: $(SSLDIR)/Makefile

$(SSLDIR)/libssl.a: $(SSLDIR)/Makefile

# HTTP Parser Build Section
#

$(HTTPDIR)/Makefile:
	git submodule update --init $(HTTPDIR)

$(HTTPDIR)/libhttp_parser.a: $(HTTPDIR)/Makefile
	$(MAKE) package -C $(HTTPDIR)

# Them phonies
#

.PHONY: dep clean test
