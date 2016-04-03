#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/types/string.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Shows<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static const String Show(const Array<T, S>& array) noexcept {
    auto out = String("Array(");
    for (size_t i = 0; i < S; i ++) {
      out = out + Shows<T>::Show(array.Pointer()[i]) + String(", ");
    }
    return Take(out, out.Length() - 2) + String(")");
  }

};

}
