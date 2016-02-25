#ifndef TRAITOROUS_CONTAINERS_OPTION_ENUMERABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_ENUMERABLE_H

#include <containers/enumerators/option_enumerator.h>
#include <containers/option.h>
#include <traits/unlawful/enumerable.h>

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template<class T>
class Enumerable<Option<T>> {
public:

  static const OptionEnumerator<T> Enumerator(const Option<T>& option) noexcept {
    return OptionEnumerator<T>(option);
  }

};

}

#endif
