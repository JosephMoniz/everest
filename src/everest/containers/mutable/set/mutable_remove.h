#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class MutableRemove<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSet<T>& RemoveInPlace(const T& item, MutableSet<T>& set) noexcept {
    return set.RemoveInPlace(item);
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  static MutableSet<T>& RemoveInPlace(const U& source, MutableSet<T>& set) noexcept {
    return set.RemoveInPlace(source);
  }

};

}