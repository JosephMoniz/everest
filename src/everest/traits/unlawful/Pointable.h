#pragma once

namespace everest {

template <class T>
class Pointable {

  typedef Pointable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U, class B>
  static constexpr B Pointer(const U& n) noexcept {
    return Base::Pointer(n);
  }

};

template <class T>
constexpr auto Pointer(const T& n) noexcept -> decltype(Pointable<T>::Pointer(n)) {
  return Pointable<T>::Pointer(n);
}

}