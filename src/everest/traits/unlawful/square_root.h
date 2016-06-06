#pragma once

#include <cmath>

namespace everest {

template <class T>
class SquareRoot {

  typedef SquareRoot<T> Base;

public:

  static constexpr bool exists = false;

  template<class U>
  static constexpr U Sqrt(const T& number) noexcept {
    return Base::Sqrt(number);
  }

};

template <class T>
class DefaultSquareRoot {
public:

  static constexpr bool exists = true;

  static constexpr auto Sqrt(const T& number) noexcept -> decltype(std::sqrt(number)) {
    return std::sqrt(number);
  }

};

template <class T>
constexpr auto Sqrt(const T& number) noexcept -> decltype(SquareRoot<T>::Sqrt(number)) {
  return SquareRoot<T>::Sqrt(number);
}

}