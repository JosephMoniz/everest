#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Findable {

  typedef Findable<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class U>
  static U& Find(const U& item, F& container) noexcept {
    return Base::Find(item, container);
  }

};

template <class F, class T>
auto Find(const T& item, F& container) noexcept -> decltype(Findable<F>::Find(item, container)) {
  return Findable<F>::Find(item, container);
}

}

#pragma clang diagnostic pop