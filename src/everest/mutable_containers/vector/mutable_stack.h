#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_stack.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableStack<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& PushInPlace(const T& item, MutableVector<T>& vector) noexcept {
    return vector.PushInPlace(item);
  }

  static MutableVector<T>& PushInPlace(T&& item, MutableVector<T>& vector) noexcept {
    return vector.PushInPlace(std::move(item));
  }

  static MutableVector<T>& PopInPlace(MutableVector<T>& vector) noexcept {
    return vector.PopInPlace();
  }

};

}
