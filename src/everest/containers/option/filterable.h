#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Filterable<Option<T>> final {
public:

  static constexpr bool exists = true;

  template <class P>
  static Option<T> Filter(P predicate, const Option<T>& option) noexcept {
    return option.Filter(predicate);
  }

};

}
