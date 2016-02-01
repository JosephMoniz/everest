#ifndef TRAITOROUS_CONTAINERS_OPTION_SHOWS_H
#define TRAITOROUS_CONTAINERS_OPTION_SHOWS_H

#include "containers/option.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template <class T>
class Shows<Option<T>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const Option<T>& n) noexcept {
    return Match(n,
      []()           { return std::string("None"); },
      [](const T& m) { return std::string("Some(") + Shows<T>::Show(m) + ")"; }
    );
  }

};

}

#endif
