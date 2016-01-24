#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_EQ_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_EQ_H

#include "traits/unlawful/eq.h"
#include "containers/local_option.h"

namespace traitorous {

template <class T>
class eq<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool equals(const local_option<T>& lhs, const local_option<T>& rhs) noexcept {
    return match(lhs,
      [&](){
        return match(rhs,
          []()           { return true; },
          [](const T& y) { return false; }
        );
      },
      [&](const T& x){
        return match(rhs,
          []()            { return false; },
          [&](const T& y) { return x == y; }
        );
      }
    );
  }

};

}

#endif
