#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_EQ_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_EQ_H

#include "containers/local_option.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

template <class T>
class Eq<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const LocalOption<T>& lhs, const LocalOption<T>& rhs) noexcept {
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
