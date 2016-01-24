#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_EQ
#define TRAITOROUS_TRAITS_EQ 1

namespace traitorous {

template <class T>
class eq {
  typedef eq<T> base;
public:
  // bool equals()
  static constexpr bool equals(const T& lhs, const T& rhs) noexcept { return base::equals(lhs, rhs); }
  static constexpr bool exists = false;
};

template <class T>
struct default_eq {
  static constexpr bool equals(const T& lhs, const T& rhs) noexcept {
    return lhs == rhs;
  }
  static constexpr bool exists = true;
};

template <class T>
constexpr inline bool equals(const T& lhs, const T& rhs) noexcept {
  return eq<T>::equals(lhs, rhs);
}

template <class T>
constexpr inline std::function<bool(const T&)> equals(const T& lhs) noexcept {
  return [&](const T& rhs) {
    return eq<T>::equals(lhs, rhs);
  };
}

template <class T>
constexpr inline bool operator==(const T& lhs, const T& rhs) noexcept {
  return eq<T>::equals(lhs, rhs);
}

template <class T>
constexpr inline bool operator!=(const T& lhs, const T& rhs) noexcept {
  return !eq<T>::equals(lhs, rhs);
}

}

#endif

#pragma clang diagnostic pop