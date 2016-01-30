#ifndef TRAITOROUS_META_MAX
#define TRAITOROUS_META_MAX 1

namespace traitorous {

template <size_t X, size_t... Xs>
struct meta_max {};

template <size_t X>
struct meta_Max<X> {
  static constexpr size_t value = X;
};

template <size_t X, size_t Y, size_t... Zs>
struct meta_Max<X, Y, Zs...> {
  static constexpr size_t value = X >= Y
                                ? meta_Max<X, Zs...>::value
                                : meta_Max<Y, Zs...>::value;
};

}

#endif
