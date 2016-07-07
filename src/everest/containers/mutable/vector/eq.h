#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Eq<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableVector<T>& lhs, const MutableVector<T>* rhs) noexcept {
    return Eq<MutableVector<T>>::Equals(&lhs, rhs);
  }

  static bool Equals(const MutableVector<T>* lhs, const MutableVector<T>& rhs) noexcept {
    return Eq<MutableVector<T>>::Equals(lhs, &rhs);
  }

  static bool Equals(const MutableVector<T>& lhs, const MutableVector<T>& rhs) noexcept {
    return Eq<MutableVector<T>>::Equals(&lhs, &rhs);
  }

  static bool Equals(const MutableVector<T>* lhs, const MutableVector<T>* rhs) noexcept {
    if (lhs == nullptr) {
      return rhs == nullptr || Pointer(*rhs) == nullptr;
    } else {
      if (rhs == nullptr) {
        return Pointer(*lhs) == nullptr;
      } else {
        auto leftLength = Length(*lhs);
        if (leftLength == Length(*rhs)) {
          auto lhsPointer = Pointer(*lhs);
          auto rhsPointer = Pointer(*rhs);
          for (size_t i = 0; i < leftLength; i++) {
            if (lhsPointer[i] != rhsPointer[i]) {
              return false;
            }
          }
          return true;
        } else {
          return false;
        }
      }
    }
  }

};

}