#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template<class T>
class Monoid<SharedOption<T>> {
public:

  static constexpr bool exists = true;

};

}