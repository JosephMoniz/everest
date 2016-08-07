#pragma once

#include <utility>

namespace everest {

template<class T>
class MaxMonoid final {

  friend class Eq<MaxMonoid<T>>;

  T _value;

public:

  MaxMonoid(const T& value) noexcept : _value(value) { }

  MaxMonoid(T&& value) noexcept : _value(std::move(value)) { }

  const T& Value() const noexcept {
    return _value;
  }

};

}

#include "everest/monoids/max/traits/eq.h"
#include "everest/monoids/max/traits/monoid.h"
#include "everest/monoids/max/traits/ord.h"
#include "everest/monoids/max/traits/semigroup.h"
#include "everest/monoids/max/traits/shows.h"
#include "everest/monoids/max/traits/zero.h"
