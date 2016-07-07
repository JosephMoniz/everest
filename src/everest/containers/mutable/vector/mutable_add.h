#pragma once

#include <everest/containers/mutable/mutable_vector.h>
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
    return PushInPlace(source, destination);
  }

  static MutableVector<T>& AddInPlace(T&& source, MutableVector<T>& destination) noexcept {
    return PushInPlace(std::move(source), destination);
  }

  static MutableVector<T>& AddInPlace(const MutableVector<T>& source, MutableVector<T>& destination) noexcept {
    destination.ReserveAtLeast(Length(destination) + Length(source));
    ForEach(source, [&](const T& item) {
      PushInPlace(item, destination);
    });
    return destination;
  }

  static MutableVector<T>& AddInPlace(MutableVector<T>&& source, MutableVector<T>& destination) noexcept {
    ForEach(source, [&](T&& item) {
      PushInPlace(std::move(item), destination);
    });
    return destination;
  }

};


}