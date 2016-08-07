#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template<class T>
class MutableRemove<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorSet<T>& RemoveInPlace(const T& item, MutableSortedVectorSet<T>& set) noexcept {
    return set.RemoveInPlace(item);
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  static MutableSortedVectorSet<T>& RemoveInPlace(const U& source, MutableSortedVectorSet<T>& set) noexcept {
    ForEach(source, [&](const T& item) {
      set.RemoveInPlace(item);
    });
  }

};

}