#ifndef TRAITOROUS_META_MIN
#define TRAITOROUS_META_MIN 1

template <size_t X, size_t... Xs>
struct meta_min {};

template <size_t X>
struct meta_min<X> {
  static constexpr size_t value = X;
};

template <size_t X, size_t Y, size_t... Zs>
struct meta_min<X, Y, Zs...> {
  static constexpr size_t value = X <= Y
                                ? meta_min<X, Zs...>::value
                                : meta_min<Y, Zs...>::value;
};

#endif
