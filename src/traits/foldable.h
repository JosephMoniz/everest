#ifndef TRAITOROUS_TRAITS_FOLDABLE
#define TRAITOROUS_TRAITS_FOLDABLE 1

#include <functional>

#include "monoid.h"

namespace traitorous {

template <class T>
struct foldable {
  // bool equals()
  static constexpr bool exists = false;
};

template <template <class> class T,
          class M,
          class = typename std::enable_if<foldable<T<M>>::exists>::type,
          class = typename std::enable_if<monoid<M>::exists>::type>
constexpr inline M fold(const T<M>& container) noexcept {
  return foldable<T<M>>::fold(container);
}

template <template <class, class> class T,
          class A,
          class M,
          class = typename std::enable_if<foldable<T<A, M>>::exists>::type,
          class = typename std::enable_if<monoid<M>::exists>::type>
constexpr inline M fold(const T<A, M>& container) noexcept {
  return foldable<T<A, M>>::fold(container);
}

template <template <class> class T,
          class A,
          class Fn,
          class M = typename std::result_of<Fn(A)>::type,
          class   = typename std::enable_if<foldable<T<A>>::exists>::type,
          class   = typename std::enable_if<monoid<M>::exists>::type>
constexpr inline M fold_map(Fn f, const T<A>& container) noexcept {
  return foldable<T<A>>::fold_map(f, container);
}

template <template <class, class> class T,
          class A,
          class B,
          class Fn,
          class M = typename std::result_of<Fn(B)>::type,
          class   = typename std::enable_if<foldable<T<A, B>>::exists>::type,
          class   = typename std::enable_if<monoid<M>::exists>::type>
constexpr inline M fold_map(Fn f, const T<A, B>& container) noexcept {
  return foldable<T<A, B>>::fold_map(f, container);
}

template <class T,
          class Fn,
          class B,
          class = typename std::enable_if<foldable<T>::exists>::type>
constexpr inline B foldr(Fn f,
                         const B& init,
                         const T& container) noexcept
{
  return foldable<T>::foldr(f, init, container);
}

template <class T,
          class Fn,
          class B,
          class = typename std::enable_if<foldable<T>::exists>::type>
constexpr inline B foldl(Fn f,
                  const B& init,
                  const T& container) noexcept
{
  return foldable<T>::foldl(f, init, container);
}

}

#endif
