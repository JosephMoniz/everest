#pragma once

#include <everest/types/string.h>
#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Shows<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableArray<T, S>& array) noexcept {
    auto out     = String("MutableArray(");
    auto pointer = array.Pointer();
    for (size_t i = 0; i < S; i ++) {
      out = std::move(out) + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(Length(out) - 2, std::move(out)) + String(")");
  }

};

}
