#pragma once

#include <everest/strings/string.h>
#include <everest/containers/checked.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Shows<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Checked<E, T>& checked) noexcept {
    return checked.Show();
  }

};

}