#pragma once

#include <utility>

namespace everest {

template<class T>
class MinMonoid final {

  friend class Eq<MinMonoid<T>>;

  T _value;

public:

  MinMonoid(const T& value) noexcept : _value(value) { }

  MinMonoid(T&& value) noexcept : _value(std::move(value)) { }

  const T& Value() const noexcept {
    return _value;
  }

};

}

#include "everest/monoids/min/traits/eq.h"
#include "everest/monoids/min/traits/monoid.h"
#include "everest/monoids/min/traits/ord.h"
#include "everest/monoids/min/traits/semigroup.h"
#include "everest/monoids/min/traits/shows.h"
#include "everest/monoids/min/traits/zero.h"
