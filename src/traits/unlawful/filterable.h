#ifndef TRAITOROUS_TRAITS_FILTERABLE
#define TRAITOROUS_TRAITS_FILTERABLE 1

#include <functional>

namespace traitorous {

template <class T>
struct filterable {
  // T filter()
  static constexpr bool exists = false;
};

template <class F,
          class P,
          class = typename std::enable_if<filterable<F>::exists>::type>
constexpr inline F filter(P p, const F& n) noexcept {
  return filterable<F>::filter(p, n);
}

}

#endif
