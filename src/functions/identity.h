#ifndef TRAITOROUS_FUNCTIONS_IDENTITY_H
#define TRAITOROUS_FUNCTIONS_IDENTITY_H

#include <functional>

#include "functions/types.h"

namespace traitorous {

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

#endif
