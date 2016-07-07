#pragma once

#include <utility>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/one.h>
#include <everest/types/int8.h>

namespace everest {

template<class T>
class StdDeviationMonoid final {

  T _sum;

  T _count;

  T _squares;

public:

  StdDeviationMonoid(const T& value) noexcept : _sum(value),
                                                _count(OneVal<T>::One()),
                                                _squares(value * value) { }

  StdDeviationMonoid(T&& value) noexcept : _sum(std::move(value)),
                                           _count(OneVal<T>::One()),
                                           _squares(value * value) { }

  const auto Value() const noexcept -> decltype(SquareRoot<T>::Sqrt(_sum)) {
    if (_count > ZeroVal<T>::Zero()) {
      return SquareRoot<T>::Sqrt(_count * _squares - (_sum * _sum)) / _count;
    } else {
      return ZeroVal<decltype(SquareRoot<T>::Sqrt(_sum))>::Zero();
    }
  }

};

}
