#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>
#include <everest/traits/unlawful/mutable/mutable_stack.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class MutableAdd<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& AddInPlace(const T& source, MutableVector<T>& destination) noexcept {
    return destination.AddInPlace(source);
  }

  static MutableVector<T>& AddInPlace(T&& source, MutableVector<T>& destination) noexcept {
    return destination.AddInPlace(std::move(source));
  }

  static MutableVector<T>& AddInPlace(const MutableVector<T>& source, MutableVector<T>& destination) noexcept {
    return destination.AddInPlace(source);
  }

  static MutableVector<T>& AddInPlace(MutableVector<T>&& source, MutableVector<T>& destination) noexcept {
    return destination.AddInPlace(std::move(source));
  }

};


}