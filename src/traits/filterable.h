#ifndef TRAITOROUS_TRAITS_FILTERABLE
#define TRAITOROUS_TRAITS_FILTERABLE 1

#include <functional>

namespace traitorous {

template <class T>
struct filterable {
  // T filter()
  static constexpr bool exists = false;
};

template <template <class> class F,
          class T,
          class = typename std::enable_if<filterable<F<T>>::exists>::type>
constexpr F<T> filter(const F<T>& n, std::function<bool(const T&)> p) noexcept {
  return filterable<T>::filter(n, p);
}

}

#endif
