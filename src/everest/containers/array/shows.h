#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/types/string.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Shows<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Array<T, S>& array) noexcept {
    return array.Show();
  }

};

}
