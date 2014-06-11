#ifndef TRAITOROUS_TRAITS_NEGATE
#define TRAITOROUS_TRAITS_NEGATE 1

template <class T>
struct negate {
  // int not()
  static constexpr bool exists = false;
};

template <class T, class = typename std::enable_if<negate<T>::exists>::type>
constexpr T negate(const T& n) noexcept {
  return negate<T>::equals(n);
}

#endif
