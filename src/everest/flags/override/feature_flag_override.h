#pragma once

#include <everest/containers/option.h>
#include "object_matcher.h"

namespace everest {

template <class I, class O>
class FeatureFlagOverride {

  ObjectMatcher<I, bool> _filter;

  O _value;

public:

  FeatureFlagOverride(ObjectMatcher<I, bool>&& filter, O&& value) noexcept : _filter(std::move(filter)),
                                                                             _value(value) { }

  Option<O&> GetOverride(const I& input) const noexcept {
    if (_filter.Accept(I::ObjectMatcher)) {
      return Option::Some(_value);
    } else {
      return Option::None();
    }
  }

};

}