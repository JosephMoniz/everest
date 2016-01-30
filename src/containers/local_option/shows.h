#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_SHOWS_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_SHOWS_H

#include "containers/local_option.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template <class T>
class Shows<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const LocalOption<T>& n) noexcept {
    return Match(n,
      []()           { return std::string("local_none"); },
      [](const T& m) { return std::string("local_some(") + Show(m) + ")"; }
    );
  }

};

}

#endif
