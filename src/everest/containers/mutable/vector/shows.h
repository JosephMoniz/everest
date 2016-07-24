#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Shows<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableVector<T>& vector) noexcept {
    return vector.Show();
  }

};

}