#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Monoid<Checked<E, T>> {
public:

static constexpr bool exists = true;

};

}