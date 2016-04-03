#pragma once

#include <everest/functions/types.h>

namespace everest {

template<class T>
T Identity(const T &n) {
  return n;
}

template<class T>
Function<const T&, T> Identity() {
  return [](const T& n) {
    return n;
  };
}

}
