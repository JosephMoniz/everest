#pragma once

#include <everest/traits/lawful/functor.h>
#include <everest/traits/lawful/monad.h>
#include <everest/functions/types.h>
#include <everest/concurrency/conveyor.h>
#include <everest/meta/nth_arg.h>

namespace everest {

template <class E, class T>
class Box final {

  std::function<void(E, T)>_open;

public:

  Box(std::function<void(E, T)> open) noexcept : _open(open) { }

  void Open(const E& error, const T& convey) noexcept {
    _open(error, convey);
  }

};

/*
template<class E, class T>
class LocalBox final {
public:

  const Consumer<Conveyor<E, T>> Open;

  LocalBox(const Consumer<Conveyor<E, T>>& open) noexcept : Open(open) { }

};

template<class E, class T>
using Box = Shared<LocalBox<E, T>>;
*/

template <class E, class T, class V>
Box<E, T> MakeBoxWithItem(const V& item) noexcept {
  return Box<E, T>([=](const E& Error, const T& Convey) {
      Convey(item);
  });
};

template <class E, class T, class V>
Box<E, T> MakeBoxWithError(const V& error) noexcept {
  return Box<E, T>([=](const E& Error, const T& Convey) {
      Error(error);
  });
};

template<class E, class T>
class Functor<Box<E, T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Box<E, B> Map(const F& f, Box<E, T>& box) noexcept {
    return Box<E, B>([=](const E& Error, const T& Convey) {
      box.Open(
        [=](const E& error) { Error(error); },
        [=](const T& item)  { Convey(f(item)); }
      );
    });
  }

};

template<class E, class T>
class Monad<Box<E, T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<nth_arg<typename std::result_of<F(T)>::type, 0>, 1>>
  static Box<E, B> FlatMap(F f, Box<E, T>& box) noexcept {
    return Box<E, B>([=](const E& Error, const T& Convey) {
      box.Open(
        [=](const E& error) { Error(error); },
        [=](const T& item) {
          f(item).Open(
            [=](const E& nextError) { Error(nextError); },
            [=](const T& nextItem)  { Convey(nextItem); }
          );
        }
      );
    });
  }

  template <class B>
  static Box<E, B> Then(Box<E, T>& first, Box<E, B>& second) noexcept {
    return Box([=](const E& Error, const T& Convey) {
      first.Open(
        [=](const E& error) { Error(error); },
        [=](const T& item) {
          second.Open(
            [=](const E& errorNext) { Error(errorNext); },
            [=](const T& itemNext)  { Convey(itemNext); }
          );
        }
      );
    });
  }

};

}

