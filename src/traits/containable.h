#ifndef TRAITOROUS_TRAITS_CONTAINABLE
#define TRAITOROUS_TRAITS_CONTAINABLE 1

#include "containers/local_option.h"

namespace traitorous {

template <class T>
struct containable {
  // bool contains()
  static constexpr bool exists = false;
};

template<class F,
         class T,
         class = typename std::enable_if<containable<F>::exists>::type>
constexpr inline bool contains(const T& n, const F& f) {
  return containable<F>::contains(n, f);
}

}

#endif
