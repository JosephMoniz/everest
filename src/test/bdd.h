#ifndef TRAITOROUS_BDD_H
#define TRAITOROUS_BDD_H

#include <cli/color.h>
#include <iostream>
#include <cstdint>

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

std::string assert(bool result) noexcept {
  __traitorous_test_total++;
  __traitorous_test_ran++;
  if (result) {
    __traitorous_test_pass++;
    return green("✔");
  } else {
    __traitorous_test_fail++;
    return red("✖");
  }
}

std::string skipped_traitorous_test(const std::string& str) {
  __traitorous_test_total++;
  __traitorous_test_skip++;
  return yellow("?") + " " + str;
}

void print_for_traitorous_test(const std::string& str) {
  for (int i = 0; i < __traitorous_test_indent; i++) {
    std::cout << "  ";
  }
  std::cout << str << std::endl;
}

void describe(const std::string& str, std::function<void()>description) noexcept {
  print_for_traitorous_test(str);
  __traitorous_test_indent++;
  description();
  __traitorous_test_indent--;
}

void it(const std::string& str, std::function<bool()>assertion) noexcept {
  print_for_traitorous_test(assert(assertion()) + " " + str);
}

void it(const std::string& str) noexcept {
  print_for_traitorous_test(skipped_traitorous_test(str));
}

int print_final_results_for_traitorous_test() {
  if (__traitorous_test_fail == 0) {
    std::cout << green("✔ ") << green(Show(__traitorous_test_total)) << green(" tests evaluated") << std::endl;
  } else {
    std::cout << red("✖ ") << red(Show(__traitorous_test_total)) << red(" tests evaluated") << std::endl;
  }

  if (__traitorous_test_pass > 0) {
    std::cout << green("  ✔ ") << Show(__traitorous_test_pass) << " tests passed" << std::endl;
  }

  if (__traitorous_test_fail > 0) {
    std::cout << red("  ✖ ") << Show(__traitorous_test_fail) << " tests failed" << std::endl;
  }

  if(__traitorous_test_skip > 0) {
    std::cout << yellow("  ? ") << Show(__traitorous_test_skip) << " tests unimplemented" << std::endl;
  }

  if (__traitorous_test_fail == 0) {
    return 0;
  } else {
    return 1;
  }
}

}

#endif