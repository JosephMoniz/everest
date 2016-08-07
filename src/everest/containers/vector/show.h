#pragma once

#include <everest/types/string.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Shows<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Vector<T>& vector) noexcept {
    return vector.Show();
  }

};

}