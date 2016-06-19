#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Eq<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableSet<T>& lhs, const MutableSet<T>* rhs) noexcept {
    return Eq<MutableSet<T>>::Equals(&lhs, rhs);
  }

  static bool Equals(const MutableSet<T>* lhs, const MutableSet<T>& rhs) noexcept {
    return Eq<MutableSet<T>>::Equals(lhs, &rhs);
  }

  static bool Equals(const MutableSet<T>& lhs, const MutableSet<T>& rhs) noexcept {
    return Eq<MutableSet<T>>::Equals(&lhs, &rhs);
  }

  static bool Equals(const MutableSet<T>* lhs, const MutableSet<T>* rhs) noexcept {
    if (lhs == nullptr) {
      return rhs == nullptr || Length(*rhs) == 0;
    } else {
      if (rhs == nullptr) {
        return Length(*lhs) == 0;
      } else {
        auto leftLength = Length(*lhs);
        if (leftLength == Length(*rhs)) {
          auto buckets = Pointer(lhs->_memory);
          for (size_t i = 0; i < leftLength; i++) {
            auto bucketLength  = Length(buckets[i]);
            auto bucketPointer = Pointer(buckets[i]);
            for (size_t j = 0; j < bucketLength; j++) {
              if (!Contains(bucketPointer[j], *rhs)) {
                return false;
              }
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