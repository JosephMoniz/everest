#ifndef TRAITOROUS_CONTAINERS_OPTION_SHOWS_H
#define TRAITOROUS_CONTAINERS_OPTION_SHOWS_H

#include "containers/option.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template <class T>
class Shows<Option<T>> {
public:

  static constexpr bool exists = true;

  static const LocalString Show(const Option<T>& n) noexcept {
    return Match(n,
      []()           { return LocalString("None"); },
      [](const T& m) { return LocalString("Some(") + Shows<T>::Show(m) + LocalString(")"); }
    );
  }

};

}

#endif
