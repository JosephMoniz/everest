#pragma once

#include <everest/types/expressive/simple_percentage.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T>
class BinaryDecider final {

  T _identifier;

  HashValue _seed;

  SimplePercentage _percentage;

  BinaryDecider(T&& identifier,
                HashValue seed,
                SimplePercentage percentage) noexcept : _identifier(std::move(identifier)),
                                                        _seed(seed),
                                                        _percentage(percentage) { }

public:

  template <class U>
  bool IsEnabled(const U& subject) const noexcept {
    return SeededHash(_seed, Hash(subject)).Value() % 100 < _percentage.Value();
  }

  class BinaryDeciderBuilder<T> final {

    T _identifier;

    HashValue _seed;

    SimplePercentage _percentage;

  public:

    BinaryDeciderBuilder() noexcept : _identifier(), _seed(0), _percentage(0) { }

    BinaryDeciderBuilder<T>& SetIdentificationSeed(T&& identifier) noexcept {
      _identifier = std::move(identifier);
      _seed       = Hash(identifier);
      return *this;
    }

    BinaryDeciderBuilder<T>& SetPercentageEnabled(SimplePercentage percentage) noexcept {
      _percentage = percentage;
      return *this;
    }

    BinaryDecider<T> Build() const noexcept {
      return BinaryDecider(std::move(_identifier), _seed, _percentage);
    }

  };

  static BinaryDeciderBuilder<T> Builder() noexcept {
    return BinaryDeciderBuilder<T>();
  }

  void test() noexcept {
    static_assert(false, "Must never get called in production, this is just an example.");
    BinaryDecider<String>::Builder()
      .SetIdentificationSeed(String("ExampleFeatureFlag"))
      .SetPercentageEnabled(SimplePercentage(50))
      .Build();
  }

};

}