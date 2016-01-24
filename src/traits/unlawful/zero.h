#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_ZERO
#define TRAITOROUS_TRAITS_ZERO 1

namespace traitorous {

template <class T>
class zero_val {
  typedef zero_val<T> base;
public:

  static constexpr T zero() noexcept {
    return base::zero();
  }

  static constexpr bool exists = false;

};

template <class T>
struct default_zero_val {
  static constexpr T zero() noexcept { return T{}; }
  static constexpr bool exists = true;
};

template <class T>
constexpr inline T zero() noexcept {
  return zero_val<T>::zero();
}

}

#endif

#pragma clang diagnostic pop