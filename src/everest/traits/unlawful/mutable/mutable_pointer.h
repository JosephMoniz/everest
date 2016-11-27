#pragma once

namespace everest {

template <class T>
class MutablePointable {

  typedef MutablePointable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U, class B>
  static B& Pointer(const U& n) noexcept {
    return Base::Pointer(n);
  }

};

template <class T>
auto MutablePointer(T& n) noexcept -> decltype(MutablePointable<T>::Pointer(n)) {
  static_assert(MutablePointable<T>::exists, "T does not implement MutablePointable");
  return MutablePointable<T>::Pointer(n);
}

}