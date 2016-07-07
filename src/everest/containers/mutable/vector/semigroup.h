#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Semigroup<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr MutableVector<T> Add(const MutableVector<T>& lhs, const MutableVector<T>& rhs) noexcept {
        auto results = MutableVector<T>(Length(lhs) + Length(rhs));
        ForEach(lhs, [&](const T& item) {
          PushInPlace(item, results);
        });
        ForEach(rhs, [&](const T& item) {
          PushInPlace(item, results);
        });
        return results;
  }

};

}