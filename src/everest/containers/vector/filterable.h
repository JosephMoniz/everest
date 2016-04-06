#pragma once

#include <utility>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template <class T>
class Filterable<Vector<T>> {
public:

 static constexpr bool exists = true;

  template<class Predicate>
  static Vector<T> Filter(Predicate predicate, const Vector<T>& vector) noexcept {
    auto results = MutableVector<T>();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (auto i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        results.Push(pointer[i]);
      }
    }
    return Vector<T>(std::move(results));
  }

};

}