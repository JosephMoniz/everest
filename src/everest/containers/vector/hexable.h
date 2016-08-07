#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Hexable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const Vector<T>& value) noexcept {
    return value.ToHex();
  }

};

}