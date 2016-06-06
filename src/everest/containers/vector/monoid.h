#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Monoid<Vector<T>> {
public:
  static constexpr bool exists = true;
};

}