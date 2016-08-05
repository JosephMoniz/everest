#pragma once

#include <everest/types/expressive/simple_percentage.h>

namespace everest {

template <class T>
class BinaryDecider<T> final {

  HashValue _seed;

  SimplePercentage _percentage;

public:

  BinaryDecider(HashValue identifier, SimplePercentage percentage) noexcept : _seed(identifier),
                                                                             _percentage(percentage) { }

  BinaryDecider(const T& identifier, SimplePercentage percentage) noexcept : _seed(Hash(identifier)),
                                                                             _percentage(percentage) { }

  template <class U>
  bool IsEnabled(const U& subject) const noexcept {
    return SeededHash(_seed.Value(), Hash(subject)).Value() % 100 < _percentage.Value();
  }

  class BinaryDeciderBuilder<T> final {

    HashValue _seed;

    SimplePercentage _percentage;

  public:

    BinaryDeciderBuilder() noexcept : _seed(0), _percentage(0) { }

    BinaryDeciderBuilder<T>& SetIdentificationSeed(const T& identifier) noexcept {
      _seed = Hash(identifier);
      return *this;
    }

    BinaryDeciderBuilder<T>& SetPercentageEnabled(SimplePercentage percentage) noexcept {
      _percentage = percentage;
      return *this;
    }

    BinaryDecider<T> Build() const noexcept {
      return BinaryDecider(_seed, _percentage);
    }

  };

  static BinaryDeciderBuilder<T> Builder() noexcept {
    return BinaryDeciderBuilder<T>();
  }

};

}