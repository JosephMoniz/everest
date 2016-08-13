#pragma once

#include <everest/strings/string.h>
#include <everest/mutable_containers/mutable_array.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Shows<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableArray<T, S>& array) noexcept {
    return array.Show();
  }

};

}
