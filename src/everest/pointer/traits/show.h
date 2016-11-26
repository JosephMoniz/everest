#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class Shows<T*> final {
public:

  static constexpr bool exists = true;

  static String Show(const T* pointer) noexcept {
    return (pointer != nullptr)
      ? Shows<T>::Show(*pointer)
      : String("nullptr");
  }

};

}