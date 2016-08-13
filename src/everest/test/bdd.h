#ifndef TRAITOROUS_BDD_H
#define TRAITOROUS_BDD_H

#include <cstdint>
#include <unistd.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/cli/color.h>
#include <everest/strings/string.h>
#include <everest/types/primitive/size.h>
#include <everest/io/process.h>
#include <everest/types/bool.h>

namespace everest {

uint32_t __traitorous_test_indent = 0;
uint32_t __traitorous_test_total  = 0;
uint32_t __traitorous_test_ran    = 0;
uint32_t __traitorous_test_pass   = 0;
uint32_t __traitorous_test_fail   = 0;
uint32_t __traitorous_test_skip   = 0;

String Assert(bool result) noexcept {
  __traitorous_test_total++;
  __traitorous_test_ran++;
  if (result) {
    __traitorous_test_pass++;
    return Green("✔");
  } else {
    __traitorous_test_fail++;
    return Red("✖");
  }
}

class AssertionException {

  String _message;

public:

  AssertionException(const String& message) noexcept : _message(Copy(message)) {}

  AssertionException(String&& message) noexcept : _message(std::move(message)) {}

};

void AssertTrue(const String& error, Bool result) {
  if (!result) {
    throw AssertionException(error);
  }
}

void AssertTrue(Bool result) {
  if (!result) {
    throw AssertionException("Should have been true but was false");
  }
}

void AssertFalse(const String& error, Bool result) {
  if (result) {
    throw AssertionException(error);
  }
}

void AssertFalse(Bool result) {
  if (result) {
    throw AssertionException("Should have been false but was true");
  }
}

template<class T>
void AssertEquals(const String& error, const T& lhs, const T& rhs) {
  if (lhs != rhs) {
    throw AssertionException(error);
  }
}

void AssertEquals(const String& lhs, const String& rhs) {
  if (lhs != rhs) {
    throw AssertionException(lhs + String(" doesn't equal ") + rhs);
  }
}

template<class T>
void AssertEquals(const T& lhs, const T& rhs) {
  if (lhs != rhs) {
    throw AssertionException(Show(lhs) + String(" doesn't equal ") + Show(rhs));
  }
}

template<class T>
void AssertEquals(const T* lhs, const T* rhs) {
  if (NotEquals(lhs, rhs)) {
    throw AssertionException(Show(lhs) + String(" doesn't equal ") + Show(rhs));
  }
}

template<class T>
void AssertNotEquals(const String& error, const T& lhs, const T& rhs) {
  if (lhs == rhs) {
    throw AssertionException(error);
  }
}

void AssertNotEquals(const String& lhs, const String& rhs) {
  if (lhs == rhs) {
    throw AssertionException(lhs + String(" equals ") + rhs);
  }
}

template<class T>
void AssertNotEquals(const T& lhs, const T& rhs) {
  if (lhs == rhs) {
    throw AssertionException(Show(lhs) + String(" equals ") + Show(rhs));
  }
}

String SkippedTraitorousTest(const String& str) {
  __traitorous_test_total++;
  __traitorous_test_skip++;
  return Yellow("?") + String(" ") + str;
}

void PrintForTraitorousTest(const String& str) {
  for (uint32_t i = 0; i < __traitorous_test_indent; i++) {
    Print(String("  "));
  }
  PrintLn(str);
}

template<class Thunk>
void Describe(const String& str, Thunk description) noexcept {
  PrintForTraitorousTest(str);
  __traitorous_test_indent++;
  description();
  __traitorous_test_indent--;
}

template<class Thunk>
void It(const String& str, Thunk test) noexcept {
  try {
    test();
    PrintForTraitorousTest(Assert(true) + String(" ") + str);
  } catch (const AssertionException& e) {
    PrintForTraitorousTest(Assert(false) + String(" ") + str);
  }
}

void It(const String& str) noexcept {
  PrintForTraitorousTest(SkippedTraitorousTest(str));
}

int PrintFinalResultsForTraitorousTest() {
  if (__traitorous_test_fail == 0) {
    Print(Green("✔ "));
    Print(Green(Show(__traitorous_test_total)));
    Print(Green(" tests evaluated\n"));
  } else {
    Print(Red("✖ "));
    Print(Red(Show(__traitorous_test_total)));
    Print(Red(" tests evaluated\n"));
  }

  if (__traitorous_test_pass > 0) {
    Print(Green("  ✔ "));
    Print(Show(__traitorous_test_pass));
    Print(String(" tests passed\n"));
  }

  if (__traitorous_test_fail > 0) {
    Print(Red("  ✖ "));
    Print(Show(__traitorous_test_fail));
    Print(String(" tests failed\n"));
  }

  if(__traitorous_test_skip > 0) {
    Print(Yellow("  ? "));
    Print(Show(__traitorous_test_skip));
    Print(String(" tests unimplemented\n"));
  }

  if (__traitorous_test_fail == 0) {
    return 0;
  } else {
    return 1;
  }
}

}

#endif
