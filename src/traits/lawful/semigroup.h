#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_SEMIGROUP
#define TRAITOROUS_TRAITS_SEMIGROUP 1

#include <functional>

namespace traitorous {

template <class T>
class semigroup {

    typedef semigroup<T> base;

public:

  static constexpr T add(const T& lhs, const T& rhs) {
    return base::add(lhs, rhs);
  }

  static constexpr bool exists = false;

};

template <class T>
class default_semigroup {
public:
  static constexpr T add(const T& lhs, const T& rhs) noexcept {
    return lhs + rhs;
  }
  static constexpr bool exists = true;
};

template <class T>
constexpr inline T add(const T& lhs, const T& rhs) noexcept {
  return semigroup<T>::add(lhs, rhs);
}

template <class T>
constexpr inline std::function<T(const T&)> add(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return semigroup<T>::add(lhs, rhs);
  };
}

template <class T>
constexpr inline std::function<T(const T&, const T&)> add() noexcept {
  return [&](const T& lhs, const T& rhs) {
    return semigroup<T>::add(lhs, rhs);
  };
}

template <class T>
constexpr inline T operator+(const T& lhs, const T& rhs) noexcept {
  return semigroup<T>::add(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop