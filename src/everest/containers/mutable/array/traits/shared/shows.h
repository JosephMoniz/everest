#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/memory/shared.h>
#include <everest/types/string.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Shows<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static const String Show(const SharedMutableArray<T, S>& array) noexcept {
    auto out     = String("SharedMutableArray(");
    auto pointer = array->Pointer();
    for (size_t i = 0; i < S; i ++) {
      out = out + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(out.Length() - 2, out) + String(")");
  }

};

}
