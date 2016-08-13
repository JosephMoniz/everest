#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/show.h>
#include <everest/strings/string.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Shows<Option<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Option<T>& option) noexcept {
    return option.Show();
  }

};

}

