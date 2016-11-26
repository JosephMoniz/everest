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
    static_assert(exists, "T does not implement Findable");
    return Base::Find(item, container);
  }

};

template <class F, class T>
auto Find(const T& item, F& container) noexcept -> decltype(Findable<F>::Find(item, container)) {
  static_assert(Findable<F>::exists, "T does not implement Findable");
  return Findable<F>::Find(item, container);
}

}

#pragma clang diagnostic pop