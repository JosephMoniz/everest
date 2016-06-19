#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Shows<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const MutableSet<T>& set) noexcept {
    auto out = String("MutableSet(");
    ForEach(set, [&](const T& item) {
      out = out + Shows<T>::Show(item) + String(", ");
    });
    return Take(Length(out) - 2, out) + String(")");
  }

};

}