#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_SHOWS_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_SHOWS_H

#include "containers/local_option.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template <class T>
class shows<local_option<T>> {
public:

  static constexpr bool exists = true;

  static const std::string show(const local_option<T>& n) noexcept {
    return match(n,
      []()           { return std::string("local_none"); },
      [](const T& m) { return std::string("local_some(") + shows<T>::show(m) + ")"; }
    );
  }

};

}

#endif
