#pragma once

#include <cmath>

namespace everest {

template <class T>
class SquareRoot {

  typedef SquareRoot<T> Base;

public:

  static constexpr bool exists = false;

  template<class U>
  static U Sqrt(const T& number) noexcept {
    static_assert(exists, "T does not implement SquareRoot");
    return Base::Sqrt(number);
  }

};

template <class T>
class DefaultSquareRoot {
public:

  static constexpr bool exists = true;

  static auto Sqrt(const T& number) noexcept -> decltype(std::sqrt(number)) {
    return std::sqrt(number);
  }

};

template <class T>
constexpr auto Sqrt(const T& number) noexcept -> decltype(SquareRoot<T>::Sqrt(number)) {
  static_assert(SquareRoot<T>::exists, "T does not implement SquareRoot");
  return SquareRoot<T>::Sqrt(number);
}

}