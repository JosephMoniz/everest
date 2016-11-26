#pragma once

#include <tuple>

namespace everest {

template <typename> struct tuplify;

template <template <typename...> class T, typename ...As>
struct tuplify<T<As...>> {
  using type = std::tuple<As...>;
};

template <typename T, unsigned int N>
using nth_type_arg = typename std::tuple_element<N, typename tuplify<T>::type>::type;

}
