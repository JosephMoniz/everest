#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class Pointable<MutableString> {
public:

  static constexpr bool exists = true;

  static const char* Pointer(const MutableString& string) noexcept {
    return Pointable<GrowableMemory<char>>::Pointer(string._data);
  }

};

}