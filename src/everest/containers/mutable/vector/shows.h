#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Shows<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const MutableVector<T>& vector) noexcept {
    auto out = String("MutableVector(");
    ForEach(vector, [&](const T& item) {
      out = out + Shows<T>::Show(item) + String(", ");
    });
    return Take(Length(out) - 2, out) + String(")");
  }

};

}