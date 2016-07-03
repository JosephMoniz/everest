#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/meta/max.h>
#include <everest/traits/unlawful/fundamental.h>
#include <everest/containers/checked/checked_type.h>

namespace everest {

template<class E, class T>
class Checked final {


  using data_t = typename std::aligned_storage<
    meta_max<sizeof(E), sizeof(T)>::value,
    meta_max<alignof(E), alignof(T)>::value
  >::type;

  CheckedType _tag;

  data_t _value;

public:

  template <class U = T>
  Checked(const CheckedType& tag, const T value, typename std::enable_if<Fundamental<U>::exists>::type* = 0) noexcept : _tag(tag) {
    new (&_value) T(value);
  }

  Checked(const CheckedType& tag, T&& value) noexcept : _tag(tag) {
    new (&_value) T(std::move(value));
  }

  template <class U = E>
  Checked(const CheckedType& tag, const E value, typename std::enable_if<Fundamental<U>::exists>::type* = 0) noexcept : _tag(tag) {
    new (&_value) E(value);
  }

  Checked(const CheckedType& tag, E&& value) noexcept : _tag(tag) {
    new (&_value) E(std::move(value));
  }

  ~Checked() noexcept {
    if (_tag == CheckedType::OK) {
      reinterpret_cast<T*>(&_value)->~T();
    } else {
      reinterpret_cast<E*>(&_value)->~E();
    }
  }

  constexpr CheckedType GetType() const noexcept {
    return _tag;
  };

  const T& Get() const noexcept {
    return *reinterpret_cast<const T*>(&_value);
  }

  T&& GetMovable() const noexcept {
    return std::move(*reinterpret_cast<T*>((data_t*)&_value));
  }

  const E& GetError() const noexcept {
    return *reinterpret_cast<const E*>(&_value);
  }

  E&& GetMovableError() const noexcept {
    return std::move(*reinterpret_cast<E*>((data_t*)&_value));
  }

  constexpr bool IsOk() const noexcept {
    return GetType() == CheckedType::OK;
  }

  constexpr bool IsError() const noexcept {
    return GetType() == CheckedType::ERROR;
  }

};

template<class E, class T>
Checked<E, T> Error(const E& error) {
  return Checked<E, T>(CheckedType::ERROR, error);
}

template<class E, class T>
Checked<E, T> Error(E&& error) {
  return Checked<E, T>(CheckedType::ERROR, std::forward<E>(error));
}


template<class E, class T>
Checked<E, T> Ok(const T& ok) {
  return Checked<E, T>(CheckedType::OK, ok);
}
template<class E, class T>
Checked<E, T> Ok(T&& ok) {
  return Checked<E, T>(CheckedType::OK, std::forward<T>(ok));
}

template <class E, class T, class Ef, class Of>
auto Match(const Checked<E, T>& checked, Ef error, Of ok) noexcept -> decltype(ok(checked.Get())) {
  return (checked.IsOk())
    ? ok(checked.Get())
    : error(checked.GetError());
}

}

#include "everest/containers/checked/alternative.h"
#include "everest/containers/checked/containable.h"
#include "everest/containers/checked/container.h"
#include "everest/containers/checked/eq.h"
#include "everest/containers/checked/foldable.h"
#include "everest/containers/checked/functor.h"
#include "everest/containers/checked/hashable.h"
#include "everest/containers/checked/monad.h"
#include "everest/containers/checked/monoid.h"
#include "everest/containers/checked/ord.h"
#include "everest/containers/checked/semigroup.h"
#include "everest/containers/checked/shows.h"
#include "everest/containers/checked/unwrappable.h"
#include "everest/containers/checked/zero.h"

#pragma clang diagnostic pop
