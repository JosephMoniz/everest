#ifndef TRAITOROUS_TRAITS_SET
#define TRAITOROUS_TRAITS_SET 1

#include "containers/option.h"

namespace traitorous {

template <class T>
struct set {
  // option<T> get()
  static constexpr bool exists = false;
};

template <template <class, class> class F
          class K,
          class V,
          class = typename std::enable_if<set<F<K, V>>::exists>::type>
constexpr option<V> get(const F<K, V>& s, const K& k) noexcept {
  return set<F<K, V>>::get(s, k);
}

}

#endif
