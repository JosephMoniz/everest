#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/memory/shared.h>
#include <everest/types/string.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Shows<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static const String Show(const SharedArray<T, S>& array) noexcept {
    auto out     = String("SharedArray(");
    auto pointer = Pointer(*array);
    for (size_t i = 0; i < S; i ++) {
      out = out + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(Length(out) - 2, out) + String(")");
  }

};

}
