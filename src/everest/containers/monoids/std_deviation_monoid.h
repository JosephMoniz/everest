#pragma once

#include <utility>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/one.h>
#include <everest/types/int8.h>
#include <everest/traits/unlawful/square_root.h>

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

  const double Value() const noexcept {
    if (_count > ZeroVal<T>::Zero()) {
      return SquareRoot<T>::Sqrt(_count * _squares - (_sum * _sum)) / _count;
    } else {
      return ZeroVal<decltype(SquareRoot<T>::Sqrt(_sum))>::Zero();
    }
  }

};

}
