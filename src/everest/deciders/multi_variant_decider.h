#pragma once

#include <everest/types/expressive/simple_percentage.h>
#include <everest/mutable_containers/mutable_sorted_vector_set.h>

namespace everest {

template <class T>
class MutliVariantDecider<T> final {

  HashValue _seed;

  SimplePercentage _percentage;

public:

  MutliVariantDecider(const T& identifier, SimplePercentage percentage) noexcept : _seed(Hash(identifier)),
                                                                                   _percentage(percentage) { }

  template <class U>
  bool IsEnabled(const U& subject) const noexcept {
    return SeededHash(_seed.Value(), Hash(subject)).Value() % 100 < _percentage.Value();
  }

};

}