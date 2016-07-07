#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/takeable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Takeable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Take(size_t length, const MutableVector<T>& vector) noexcept {
    return MutableVector<T>(MutableMemory<T>(Pointer(vector), Min(length, Length(vector))));
  }

  template<class Predicate>
  static MutableVector<T> TakeWhile(Predicate predicate, const MutableVector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = Length(vector);
    auto pointer  = Pointer(vector);
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return MutableVector<T>(MutableMemory<T>(pointer, offset));
  }

};

}