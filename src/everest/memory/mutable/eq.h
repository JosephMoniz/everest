#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/memory/mutable/eq.h>

namespace everest {

template <class T>
class MutableMemory;

template<class T>
class Eq<MutableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableMemory<T>& lhs, const MutableMemory<T>* rhs) noexcept {
    return Equals(&lhs, rhs);
  }

  static bool Equals(const MutableMemory<T>* lhs, const MutableMemory<T>& rhs) noexcept {
    return Equals(lhs, &rhs);
  }

  static bool Equals(const MutableMemory<T>& lhs, const MutableMemory<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

  static bool Equals(const MutableMemory<T>* lhs, const MutableMemory<T>* rhs) noexcept {
    if (lhs == nullptr) {
      return rhs == nullptr || rhs->Pointer() == nullptr;
    } else {
      if (rhs == nullptr) {
        return lhs->Pointer() == nullptr;
      } else {
        return lhs->Equals(*rhs);
      }
    }
  }

};

}