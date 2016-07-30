#pragma once

#include <everest/memory/growable_memory.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T>
class GrowableMemory;

template<class T>
class Eq<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GrowableMemory<T>& lhs, const GrowableMemory<T>* rhs) noexcept {
    return Equals(&lhs, rhs);
  }

  static bool Equals(const GrowableMemory<T>* lhs, const GrowableMemory<T>& rhs) noexcept {
    return Equals(lhs, &rhs);
  }

  static bool Equals(const GrowableMemory<T>& lhs, const GrowableMemory<T>& rhs) noexcept {
    return Equals(&lhs, &rhs);
  }

  static bool Equals(const GrowableMemory<T>* lhs, const GrowableMemory<T>* rhs) noexcept {
    if (lhs == nullptr) {
      return rhs == nullptr || Pointer(*rhs) == nullptr;
    } else {
      if (rhs == nullptr) {
        return Pointer(*lhs) == nullptr;
      } else {
        return lhs->Equals(*rhs);
      }
    }
  }

};

}