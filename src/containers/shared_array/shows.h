#pragma once

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Shows<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static const String Show(const SharedArray<T, S>& array) noexcept {
    auto out = String("SharedArray(");
    for (size_t i = 0; i < S; i ++) {
      out = out + Shows<T>::Show(array->Pointer()[i]) + String(", ");
    }
    return Take(out, out.Length() - 2) + String(")");
  }

};

}
