#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_SHOWS_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_SHOWS_H

#include <containers/chain.h>
#include <containers/option.h>
#include <traits/unlawful/show.h>

namespace traitorous {

template <class T>
class LocalOption;

template <class T>
class Shows<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static const LocalString Show(const LocalOption<T>& n) noexcept {
    return Match(n,
      []()           { return LocalString("LocalNone"); },
      [](const T& m) { return LocalString("LocalSome(") + Shows<T>::Show(m) + LocalString(")"); }
    );
  }

};

}

#endif
