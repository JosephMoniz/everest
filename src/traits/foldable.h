#ifndef TRAITOROUS_TRAITS_EQ
#define TRAITOROUS_TRAITS_EQ 1

#include <functional>

namespace traitorous {

template <class T>
struct foldable {
  // bool equals()
  static constexpr bool exists = false;
};

template <template <class> class T,
          class M,
          class = typename std::enable_if<foldable<T>::exists>::type,
          class = typename std::enable_if<monoid<M>::exists>::type>
constexpr M fold(const T<M>& container) noexcept {
  return foldable<T>::fold(container);
}

template <template <class> class T,
          class A,
          class M,
          class = typename std::enable_if<foldable<T>::exists>::type,
          class = typename std::enable_if<monoid<M>::exists>::type>
constexpr M foldMap(std::function<M(const A&)> f, const T<M>& container) noexcept {
  return foldable<T>::foldMap(f, container);
}

template <template <class> class T,
          class A,
          class B,
          class = typename std::enable_if<foldable<T>::exists>::type>
constexpr B foldr(std::function<B(const A&, const B&)> f,
                  const B& init,
                  const T<A>&, container)
{
  return foldable<T>::foldr(f, init, container);
}

template <template <class> class T,
          class A,
          class B,
          class = typename std::enable_if<foldable<T>::exists>::type>
constexpr A foldl(std::function<A(const B&, const A&)> f,
                  const A& init,
                  const T<B>&, container)
{
  return foldable<T>::foldr(f, init, container);
}

}

#endif
