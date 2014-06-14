#ifndef TRAITOROUS_TRAITS_TRAVERSABLE
#define TRAITOROUS_TRAITS_TRAVERSABLE 1

#include <functional>

#include "applicative.h"
#include "functor.h"
#include "foldable.h"
#include "monad.h"


namespace traitorous {

template <class T>
struct traversable {
  // traverse()
  // sequenceA()
  // mapM()
  // sequence()
  static constexpr bool exists = false;
};

template <template <class> class T,
          template <class> class F,
          class A,
          class B,
          class = typename std::enable_if<functor<T<A>>::exists>::type,
          class = typename std::enable_if<foldable<T<A>>::exists>::type,
          class = typename std::enable_if<applicative<F<B>>::exists>::type>
constexpr F<T<A>> traverse(std::function<F<B>(const A&)>f, const T<A>& t) noexcept {
  return traversable<T<A>>::traverse(f, t);
}

template <template <class> class T,
          template <class> class F,
          class A,
          class B,
          class = typename std::enable_if<functor<T<A>>::exists>::type,
          class = typename std::enable_if<foldable<T<A>>::exists>::type,
          class = typename std::enable_if<applicative<F<A>>::exists>::type>
constexpr F<T<A>> sequenceA(const T<F<A>>& t) noexcept {
  return traversable<T<A>>::sequenceA(t);
}

template <template <class> class F,
          template <class> class M,
          class A,
          class B,
          class = typename std::enable_if<functor<T<A>>::exists>::type,
          class = typename std::enable_if<foldable<T<A>>::exists>::type,
          class = typename std::enable_if<monad<M<B>>::exists>::type>
constexpr M<T<B>> mapM(std::function<M<B>(const A&)> f, const T<A>& t) noexcept {
  return traversable<T<A>>::mapM(lhs, rhs);
}

template <template <class> class F,
          template <class> class M,
          class A,
          class B,
          class = typename std::enable_if<functor<T<A>>::exists>::type,
          class = typename std::enable_if<foldable<T<A>>::exists>::type,
          class = typename std::enable_if<monad<M<A>>::exists>::type>
constexpr M<T<A>> mapM(const T<M<A>>& t) noexcept {
  return traversable<T<A>>::sequence(t);
}

}

#endif
