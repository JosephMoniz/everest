#pragma once

#include <everest/mutable_containers/mutable_vector.h>
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
    return lhs.Equals(rhs);
  }

  static bool Equals(const MutableVector<T>* lhs, const MutableVector<T>* rhs) noexcept {
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