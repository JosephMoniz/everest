#ifndef TRAITOROUS_META_NTHARG
#define TRAITOROUS_META_NTHARG 1

#include <tuple>

namespace traitorous {

template <typename> struct tuplify;

template <template <typename...> class T, typename ...As>
struct tuplify<T<As...>> {
  using type = std::tuple<As...>;
};

template <typename T, unsigned int N>
using nth_arg = typename std::tuple_element<N, typename tuplify<T>::type>::type;

}

#endif
