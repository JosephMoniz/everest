#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Filterable<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSet<T> Filter(Predicate predicate, const MutableSet<T>& set) noexcept {
    auto results = MutableSet<T>();
    ForEach(set, [&](const T& item) {
      if (predicate(item)) {
        AddInPlace(item, results);
      }
    });
    return results;
  }

};

}