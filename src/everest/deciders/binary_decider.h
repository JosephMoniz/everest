#pragma once

#include <everest/types/expressive/simple_percentage.h>

namespace everest {

template <class T>
class BinaryDecider<T> final {

  HashValue _seed;

  SimplePercentage _percentage;

public:

  BinaryDecider(const T& identifier, SimplePercentage percentage) noexcept : _seed(Hash(identifier)),
                                                                             _percentage(percentage) { }

  template <class U>
  bool IsEnabled(const U& subject) const noexcept {
     return SeededHash(_seed.Value(), Hash(subject)).Value() % 100 < _percentage.Value();
  }

};

}