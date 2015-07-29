#ifndef TRAITOROUS_FUNCTIONS_IDENTITY_H
#define TRAITOROUS_FUNCTIONS_IDENTITY_H

#include <functional>

namespace traitorous {

template<class T>
T identity(const T &n) {
  return n;
}

template<class T>
std::function<T(const T &)> identity() {
  return [](const T &n) {
    return n;
  };
}

}

#endif
