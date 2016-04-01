#pragma once

#include <everest/containers/shared.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/containers/list.h>

namespace traitorous {

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class Monoid<List<T>> {
public:
  static constexpr bool exists = true;
};

}
