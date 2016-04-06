#pragma once

#include <everest/containers/option.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/stack.h>

namespace everest {

template <class T>
struct Stack<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Push(const T& item, const Vector<T>& vector) noexcept {
    auto capacity = vector.Length() + 1;
    auto memory   = MutableMemory<T>(vector.Pointer(), capacity);
    memory.MutablePointer()[capacity] = item;
    return Vector<T>(Memory<T>(memory));
  }

  static Vector<T> Pop(const Vector<T>& vector) noexcept {
    return Vector<T>(Memory<T>(vector.Pointer(), Max(vector.Length() - 1, 0)));
  }

  static Option<const T&> Top(const Vector<T>& vector) noexcept {
    auto length = vector.Length();
    if (length > 0) {
      return Some(vector.Pointer()[length - 1]);
    } else {
      return None<const T&>();
    }
  }

};

}