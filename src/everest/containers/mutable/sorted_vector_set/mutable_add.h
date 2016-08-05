#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template<class T>
class MutableAdd<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorSet<T>& AddInPlace(const T& source, MutableSortedVectorSet<T>& destination) noexcept {
    return destination.AddInPlace(source);
  }

  static MutableSortedVectorSet<T>& AddInPlace(T&& source, MutableSortedVectorSet<T>& destination) noexcept {
    return destination.AddInPlace(std::move(source));
  }

  static MutableSortedVectorSet<T>& AddInPlace(const MutableSortedVectorSet<T>& source,
                                               MutableSortedVectorSet<T>& destination) noexcept
  {
    return destination.AddInPlace(source);
  }

  static MutableSortedVectorSet<T>& AddInPlace(MutableSortedVectorSet<T>&& source,
                                               MutableSortedVectorSet<T>& destination) noexcept
  {
    return destination.AddInPlace(std::move(source));
  }

};

}