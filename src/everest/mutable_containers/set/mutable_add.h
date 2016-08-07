#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class MutableAdd<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSet<T>& AddInPlace(const T& source, MutableSet<T>& destination) noexcept {
    return destination.AddInPlace(source);
  }

  static MutableSet<T>& AddInPlace(T&& source, MutableSet<T>& destination) noexcept {
    return destination.AddInPlace(std::move(source));
  }

  static MutableSet<T>& AddInPlace(const MutableSet<T>& source, MutableSet<T>& destination) noexcept {
    return destination.AddInPlace(source);
  }

  static MutableSet<T>& AddInPlace(MutableSet<T>&& source, MutableSet<T>& destination) noexcept {
    return destination.AddInPlace(std::move(source));
  }

};

}