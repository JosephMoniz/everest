#pragma once

#include <containers/enumerators/option_enumerator.h>
#include <containers/option.h>
#include <traits/unlawful/enumerable.h>

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template<class T>
class Enumerable<SharedOption<T>> {
public:

  static const OptionEnumerator<T> Enumerator(const SharedOption<T>& option) noexcept {
    return OptionEnumerator<T>(option);
  }

};

}
