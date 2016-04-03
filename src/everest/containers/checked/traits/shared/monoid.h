#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Monoid<SharedChecked<E, T>> {
public:

static constexpr bool exists = true;

};

}