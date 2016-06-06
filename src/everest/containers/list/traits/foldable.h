#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/list.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T>
using List = Shared<LocalList<T>>;

template <class T>
class Foldable<List<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const List<T>& list) noexcept {
    T memo = ZeroVal<T>::Zero();
    for (auto it = list->Head(); Pointer(it) != nullptr; it = it->Next()) {
      memo = Semigroup<T>::Add(memo, it->Item());
    }
    return memo;
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const List<T>& list) noexcept {
    T memo = ZeroVal<T>::Zero();
    for (auto it = list->Head(); Pointer(it) != nullptr; it = it->Next()) {
      memo = Semigroup<T>::Add(memo, f(it->Item()));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const List<T>& list) noexcept
  {
    auto reversed = Foldable<List<T>>::FoldL(
      [](auto memo, auto item) { return Cons(item, memo); },
      Cons<T>(),
      list
    );

    return Foldable<List<T>>::FoldL(f, init, reversed);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const List<T>& list) noexcept
  {
    B memo = init;
    for (auto it = list->Head(); Pointer(it) != nullptr; it = it->Next()) {
      memo = f(memo, it->Item());
    }
    return memo;
  }

};

}

