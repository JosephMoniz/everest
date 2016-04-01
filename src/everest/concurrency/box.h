#pragma once

#include <everest/traits/lawful/functor.h>
#include <everest/traits/lawful/monad.h>
#include <everest/functions/types.h>
#include <everest/concurrency/conveyor.h>
#include <everest/meta/nth_arg.h>

namespace traitorous {

template<class E, class T>
class LocalBox {
public:

  const Consumer<Conveyor<E, T>> Open;

  LocalBox(const Consumer<Conveyor<E, T>>& open) noexcept : Open(open) { }

};

template<class E, class T>
using Box = Shared<LocalBox<E, T>>;

template<class E, class T>
const Box<E, T> MakeBox(const Consumer<Conveyor<E, T>>& open) noexcept {
  return MakeShared<LocalBox<E, T>>(open);
};

template<class E, class T>
const Box<E, T> MakeBoxWithItem(const T& item) noexcept {
  return MakeBox<E, T>([=](const Conveyor<E, T>& conveyor) {
      conveyor->Convey(item);
  });
};

template<class E, class T>
const Box<E, T> MakeBoxWithError(const E& error) noexcept {
  return MakeBox<E, T>([=](const Conveyor<E, T>& conveyor) {
      conveyor->Error(error);
  });
};

template<class E, class T>
class Functor<Box<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static const Box<E, B> Map(const F& f, const Box<E, T>& box) noexcept {
    return MakeBox<E, B>([=](const Conveyor<E, B>& conveyor) {
      box->Open(MakeConveyor<E, T>(
        [=](const E& error) { conveyor->Error(error); },
        [=](const T& item)  { conveyor->Convey(f(item)); }
      ));
    });
  }

};

template<class E, class T>
class Monad<Box<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<nth_arg<typename std::result_of<F(T)>::type, 0>, 1>>
  static constexpr Box<E, B> FlatMap(F f, const Box<E, T>& box) noexcept {
    return MakeBox<E, B>([=](const Conveyor<E, T>& conveyor) {
      box->Open(MakeConveyor<E, T>(
        [=](const E& error) { conveyor->Error(error); },
        [=](const T& item) {
          f(item)->Open(MakeConveyor<E, B>(
            [=](const E& nextError) { conveyor->Error(nextError); },
            [=](const T& nextItem)  { conveyor->Convey(nextItem); }
          ));
        }
      ));
    });
  }

  template <class B>
  static constexpr Box<E, B> Then(const Box<E, T>& first, const Box<E, B>& second) noexcept {
    return MakeBox([=](const Conveyor<E, T>& conveyor) {
      first->Open(MakeConveyor<E, T>(
        [=](const E& error) { conveyor->Error(error); },
        [=](const T& item) {
          second->Open(MakeConveyor<E, T>(
            [=](const E& errorNext) { conveyor->Error(errorNext); },
            [=](const T& itemNext)  { conveyor->Convey(itemNext); }
          ));
        }
      ));
    });
  }

};

}

