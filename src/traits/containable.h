#ifndef TRAITOROUS_TRAITS_CONTAINABLE
#define TRAITOROUS_TRAITS_CONTAINABLE 1

namespace traitorous {

template <class T>
struct containable {
  // bool contains()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class T,
          class = typename std::enable_if<containable<F<T>>::exists>::type>
constexpr bool contains(const F<T>& f, const T& n) noexcept {
  return containable<F<T>>::contains(f, n);
}

}

#endif
