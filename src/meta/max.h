#ifndef TRAITOROUS_META_MAX
#define TRAITOROUS_META_MAX 1

namespace traitorous {

template <size_t X, size_t... Xs>
struct meta_max {};

template <size_t X>
struct meta_max<X> {
  static constexpr size_t value = X;
};

template <size_t X, size_t Y, size_t... Zs>
struct meta_max<X, Y, Zs...> {
  static constexpr size_t value = X >= Y
                                ? meta_max<X, Zs...>::value
                                : meta_max<Y, Zs...>::value;
};

}

#endif
