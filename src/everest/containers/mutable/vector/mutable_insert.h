#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_insert.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableInsert<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& InsertInPlace(const T& item, size_t position, MutableVector<T>& vector) noexcept {
    return vector.InsertInPlace(item, position);
  }

  static MutableVector<T>& InsertInPlace(T&& item, size_t position, MutableVector<T>& vector) noexcept {
    return vector.InsertInPlace(std::move(item), position);
  }

};

}
