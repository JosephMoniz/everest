#pragma once

#include <cassert>
#include <everest/containers/option.h>

namespace everest {

class SimplePercentage final {

  unsigned int _percentage;

public:

  SimplePercentage(unsigned int percentage) noexcept : _percentage(percentage) {
    assert(percentage >= 0 && percentage <= 100);
  }

  static Option<SimplePercentage> of(unsigned int percentage) noexcept {
    return (percentage >= 0 && percentage <= 100)
      ? Some(SimplePercentage(percentage))
      : None();
  }

  unsigned int Value() const noexcept {
    return _percentage;
  }

};

}