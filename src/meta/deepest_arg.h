#ifndef TRAITOROUS_META_DEEPEST_ARG_H
#define TRAITOROUS_META_DEEPEST_ARG_H

namespace traitorous {

template <class>
struct deepest_arg;

template <template <class> class T, class X>
struct deepest_arg<T<X>> {
  using type = deepest_arg<X>;
};

template <class X>
struct deepest_arg<X> {
  using type = X;
};

}

#endif
