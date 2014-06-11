#ifndef TRAITOROUS_TRAITS_ONE
#define TRAITOROUS_TRAITS_ONE 1

template <class T>
struct one_val {
  // T one()
  static constexpr bool exists = false;
};

template <class T, class = typename std::enable_if<one_val<T>::exists>::type>
constexpr T one() noexcept {
  return one_val<T>::one();
}

#endif
