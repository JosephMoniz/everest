#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_SHOWS_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_SHOWS_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template <class T, size_t S>
class Shows<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const LocalArray<T, S>& array) noexcept {
    std::string out = "LocalArray(";
    for (size_t i = 0; i < S; i ++) {
      out += Shows<T>::Show(array.pointer()[i]) + ", ";
    }
    out = out.substr(0, out.length() - 2);
    out += ")";
    return out;
  }

};

}

#endif
