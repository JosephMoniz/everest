#ifndef TRAITOROUS_FUNCTIONS_IDENTITY_H
#define TRAITOROUS_FUNCTIONS_IDENTITY_H

#include <functional>

namespace traitorous {

template<class T>
T Identity(const T &n) {
  return n;
}

template<class T>
std::function<T(const T &)> Identity() {
  return [](const T &n) {
    return n;
  };
}

}

#endif
