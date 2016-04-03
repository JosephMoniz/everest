#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class ZeroVal<SharedChecked<E, T>> {
public:

static constexpr bool exists = true;

static constexpr SharedChecked<E, T> Zero() {
  return MakeSharedOk<E, T>(ZeroVal<T>::Zero());
}

};

}