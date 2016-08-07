#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class T>
class Option;

template<class T>
class Ord<Option<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const Option<T>& Min(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const Option<T>& Max(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}
