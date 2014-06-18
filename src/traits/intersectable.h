#ifndef TRAITOROUS_TRAITS_INTERSECTABLE
#define TRAITOROUS_TRAITS_INTERSECTABLE 1

namespace traitorous {

template <class T>
struct intersectable {
  // T intersect()
  static constexpr bool exists = false;
};

template <class T,
          class = typename std::enable_if<intersectable<T>::exists>::type>
constexpr T inetsect(const T& a, const T& b) noexcept {
  return intersectable<T>::intersect(a, b);
}

}

#endif
