#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/stack.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
struct Stack<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Push(const T& item, const MutableVector<T>& vector) noexcept {
    auto capacity = Length(vector) + 1;
    auto memory   = MutableMemory<T>(Pointer(vector), capacity);
    MutablePointer(memory)[capacity] = item;
    return MutableVector<T>(memory);
  }

  static MutableVector<T> Pop(const Vector<T>& vector) noexcept {
    return MutableVector<T>(MutableMemory<T>(Pointer(vector), Max(Length(vector) - 1, 0)));
  }

  static Option<const T&> Top(const Vector<T>& vector) noexcept {
    return vector.At(Length(vector) - 1);
  }

};

}