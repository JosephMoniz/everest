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
constexpr M fold(const T<M>& container) noexcept {
  return foldable<T<M>>::fold(container);
}

template <template <class> class T,
          class A,
          class M,
          class = typename std::enable_if<foldable<T<A>>::exists>::type,
          class = typename std::enable_if<monoid<M>::exists>::type>
constexpr M foldMap(std::function<M(const A&)> f,
                    const T<A>& container) noexcept
{
  return foldable<T<A>>::foldMap(f, container);
}

template <template <class> class T,
          class A,
          class B,
          class = typename std::enable_if<foldable<T<A>>::exists>::type>
constexpr B foldr(std::function<B(const B&, const A&)> f,
                  const B& init,
                  const T<A>& container) noexcept
{
  return foldable<T<A>>::foldr(f, init, container);
}

template <template <class> class T,
          class A,
          class B,
          class = typename std::enable_if<foldable<T<A>>::exists>::type>
constexpr B foldl(std::function<B(const B&, const A&)> f,
                  const B& init,
                  const T<A>& container) noexcept
{
  return foldable<T<A>>::foldl(f, init, container);
}

}

#endif
