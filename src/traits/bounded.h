#ifndef TRAITOROUS_TRAITS_BOUNDED
#define TRAITOROUS_TRAITS_BOUNDED 1

#include <limits>

template <class T>
struct bounded {
  // T min_value()
  // T max_value()
  static constexpr bool exists = false;
};

template <class T>
struct default_bounded {
  static constexpr T min_value() noexcept {
    return std::numeric_limits<T>::min();
  }
  static constexpr T max_value() noexcept {
    return std::numeric_limits<T>::max();
  }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<bounded<T>::exists>::type>
constexpr T min_value() noexcept {
  return bounded<T>::min_value();
}

template <class T, class = typename std::enable_if<bounded<T>::exists>::type>
constexpr T max_value() noexcept {
  return bounded<T>::max_value();
}

#endif
