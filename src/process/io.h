#ifndef TRAITOROUS_PROCESS_IO_H
#define TRAITOROUS_PROCESS_IO_H

#include <cstdint>
#include <unistd.h>

namespace traitorous {

void Print(const LocalString& string) noexcept {
  write(1, string.CString(), string.Capacity());
}

void PrintLn(const LocalString& string) noexcept {
  write(1, string.CString(), string.Capacity());
  write(1, "\n", 1);
}

}

#endif
