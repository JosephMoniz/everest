#pragma once

#include <everest/containers/option.h>
#include <everest/memory/shared.h>
#include <everest/containers/enumerators/option_enumerator.h>
#include <everest/traits/unlawful/enumerable.h>

namespace everest {

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
