#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>
#include <everest/containers/option/traits/container.h>

namespace everest {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Container<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const SharedOption<T>& o) noexcept {
    return Container<Option<T>>::Length(*o);
  }

  static constexpr bool IsEmpty(const SharedOption<T>& o) noexcept {
    return Container<Option<T>>::IsEmpty(*o);
  }

};

}
