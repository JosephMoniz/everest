#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template<class T>
class Functor<Vector<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Vector<B> Map(F f, const Vector<T>& vector) noexcept {
    auto length = vector.Length();
    auto memory = MutableMemory<B>(length);
    auto source = vector.Pointer();
    auto dest   = memory.MutablePointer();
    for (size_t i = 0; i < length; i++) {
      dest[i] = f(source[i]);
    }
    return Vector<T>(Memory<T>(memory));
  }

};

}