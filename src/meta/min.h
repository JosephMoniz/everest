#pragma once

namespace traitorous {

template <size_t X, size_t... Xs>
struct meta_min {};

template <size_t X>
struct meta_Min<X> {
  static constexpr size_t value = X;
};

template <size_t X, size_t Y, size_t... Zs>
struct meta_Min<X, Y, Zs...> {
  static constexpr size_t value = X <= Y
                                ? meta_Min<X, Zs...>::value
                                : meta_Min<Y, Zs...>::value;
};

}
