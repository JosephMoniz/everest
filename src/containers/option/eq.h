#ifndef TRAITOROUS_CONTAINERS_OPTION_EQ_H
#define TRAITOROUS_CONTAINERS_OPTION_EQ_H

#include "containers/option.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

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

#endif
