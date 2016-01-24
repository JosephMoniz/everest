#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_CONTAINER
#define TRAITOROUS_TRAITS_CONTAINER 1

#include <type_traits>

namespace traitorous {

template <class T>
class container {
  typedef container<T> base;
public:

  static constexpr size_t length(const T& n) {
    return base::length(n);
  }

  static constexpr bool is_empty(const T& n) {
    return base::is_empty(n);
  }

  static constexpr bool exists = false;
};

template<class T>
constexpr inline size_t length(const T& n) noexcept {
  return container<T>::length(n);
}

template<class T>
constexpr inline bool is_empty(const T& n) noexcept {
  return container<T>::is_empty(n);
}

}

#endif

#pragma clang diagnostic pop