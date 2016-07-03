#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class ZeroVal<Checked<E, T>> {
public:

static constexpr bool exists = true;

static constexpr Checked<E, T> Zero() {
  return Ok<E, T>(ZeroVal<T>::Zero());
}

};

}