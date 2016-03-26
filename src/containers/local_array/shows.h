#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_SHOWS_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_SHOWS_H

#include <string>

#include <stddef.h>

#include <containers/array.h>
#include <traits/unlawful/show.h>

namespace traitorous {

template <class T, size_t S>
class LocalArray;

template <class T, size_t S>
class Shows<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static const LocalString Show(const LocalArray<T, S>& array) noexcept {
    auto out = LocalString("LocalArray(");
    for (size_t i = 0; i < S; i ++) {
      out = out + Shows<T>::Show(array.Pointer()[i]) + LocalString(", ");
    }
    return Take(out, out.Length() - 2) + LocalString(")");
  }

};

}

#endif
