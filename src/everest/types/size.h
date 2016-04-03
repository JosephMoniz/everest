#pragma once

#include <stddef.h>
#include <everest/types/string.h>
#include <everest/containers/mutable/mutable_memory.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

// TODO: this seems pretty sketch, should ensure it aligns
//       with the correct size of the systems size_t

template <>
class Shows<size_t> {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(size_t number) noexcept {
    if (number < 10u)         return 1;
    if (number < 100u)        return 2;
    if (number < 1000u)       return 3;
    if (number < 10000u)      return 4;
    if (number < 100000u)     return 5;
    if (number < 1000000u)    return 6;
    if (number < 10000000u)   return 7;
    if (number < 100000000u)  return 8;
    if (number < 1000000000u) return 9;
    return 10;
  }

  static const String Show(size_t number) noexcept {
    auto size     = NumDigits(number);
    auto offset   = size;
    auto capacity = size + 1;
    auto memory   = MutableMemory<char>(capacity);
    auto pointer  = memory.MutablePointer();
    for (auto i = size; i; i--) {
      pointer[--offset] = (char) (number % 10) + '0';
      number /= 10;
    };
    pointer[capacity - 1] = '\0';
    return String(std::move(memory), size);
  }

};

}
