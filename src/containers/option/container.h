#ifndef TRAITOROUS_CONTAINERS_OPTION_CONTAINER_H
#define TRAITOROUS_CONTAINERS_OPTION_CONTAINER_H

#include "containers/option.h"
#include "traits/unlawful/container.h"

namespace traitorous {

template <class T>
class Container<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Option<T>& o) noexcept {
    return Container<LocalOption<T>>::Length(*o.pointer());
  }

  static constexpr bool IsEmpty(const Option<T>& o) noexcept {
    return Container<LocalOption<T>>::IsEmpty(*o.pointer());
  }

};

}

#endif
