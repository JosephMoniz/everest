#ifndef TRAITOROUS_BDD_H
#define TRAITOROUS_BDD_H

#include <cstdint>
#include <unistd.h>

#include "cli/color.h"
#include "traits/unlawful/show.h"

#include "types/string.h"
#include "types/int32.h"

namespace traitorous {

int32_t __traitorous_test_indent = 0;
int32_t __traitorous_test_total  = 0;
int32_t __traitorous_test_ran    = 0;
int32_t __traitorous_test_pass   = 0;
int32_t __traitorous_test_fail   = 0;
int32_t __traitorous_test_skip   = 0;

std::string Assert(bool result) noexcept {
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

std::string SkippedTraitorousTest(const std::string &str) {
  __traitorous_test_total++;
  __traitorous_test_skip++;
  return Yellow("?") + " " + str;
}

void PrintForTraitorousTest(const std::string &str) {
  for (int i = 0; i < __traitorous_test_indent; i++) {
    write(1, "  ", 2);
  }
  write(1, str.c_str(), str.length());
  write(1, "\n", 1);
}

void Describe(const std::string &str, std::function<void()> description) noexcept {
  PrintForTraitorousTest(str);
  __traitorous_test_indent++;
  description();
  __traitorous_test_indent--;
}

void It(const std::string &str, std::function<bool()> assertion) noexcept {
  PrintForTraitorousTest(Assert(assertion()) + " " + str);
}

void It(const std::string &str) noexcept {
  PrintForTraitorousTest(SkippedTraitorousTest(str));
}

int PrintFinalResultsForTraitorousTest() {
  if (__traitorous_test_fail == 0) {
    std::string mark  = Green("✔ ");
    std::string count = Green(Show(__traitorous_test_total));
    std::string trail = Green(" tests evaluated\n");
    write(1, mark.c_str(), mark.length());
    write(1, count.c_str(), count.length());
    write(1, trail.c_str(), trail.length());
  } else {
    std::string mark  = Red("✖ ");
    std::string count = Red(Show(__traitorous_test_total));
    std::string trail = Red(" tests evaluated\n");
    write(1, mark.c_str(), mark.length());
    write(1, count.c_str(), count.length());
    write(1, trail.c_str(), trail.length());
  }

  if (__traitorous_test_pass > 0) {
    std::string mark  = Green("  ✔ ");
    std::string count = Show(__traitorous_test_pass);
    std::string trail = " tests passed\n";
    write(1, mark.c_str(), mark.length());
    write(1, count.c_str(), count.length());
    write(1, trail.c_str(), trail.length());
  }

  if (__traitorous_test_fail > 0) {
    std::string mark  = Red("  ✖ ");
    std::string count = Show(__traitorous_test_fail);
    std::string trail = " tests failed\n";
    write(1, mark.c_str(), mark.length());
    write(1, count.c_str(), count.length());
    write(1, trail.c_str(), trail.length());
  }

  if(__traitorous_test_skip > 0) {
    std::string mark  = Yellow("  ? ");
    std::string count = Show(__traitorous_test_skip);
    std::string trail = " tests unimplemented\n";
    write(1, mark.c_str(), mark.length());
    write(1, count.c_str(), count.length());
    write(1, trail.c_str(), trail.length());
  }

  if (__traitorous_test_fail == 0) {
    return 0;
  } else {
    return 1;
  }
}

}

#endif