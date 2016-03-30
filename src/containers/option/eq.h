#pragma once

#include "containers/option.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

template <class T>
class Option;

template <class T>
class Eq<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return Match(lhs,
      [&](){
        return Match(rhs,
          []()           { return true; },
          [](const T& y) { return false; }
        );
      },
      [&](const T& x){
        return Match(rhs,
          []()            { return false; },
          [&](const T& y) { return x == y; }
        );
      }
    );
  }

};

}
