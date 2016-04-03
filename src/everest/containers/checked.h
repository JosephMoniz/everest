#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/meta/max.h>
#include <everest/containers/shared.h>
#include <everest/containers/checked/checked_type.h>

namespace everest {

template<class E, class T>
class Checked final {


  using data_t = typename std::aligned_storage<
    meta_max<sizeof(E), sizeof(T)>::value,
    meta_max<alignof(E), alignof(T)>::value
  >::type;

  const CheckedType _tag;

  data_t _value;

public:

  Checked(const CheckedType& tag, const T& value) noexcept : _tag(tag) {
    new (&_value) T(value);
  }

  Checked(const CheckedType& tag, T&& value) noexcept : _tag(tag) {
    _value = std::move(value);
  }

  Checked(const CheckedType& tag, const E& value) noexcept : _tag(tag) {
    new (&_value) E(value);
  }

  Checked(const CheckedType& tag, E&& value) noexcept : _tag(tag) {
    _value = std::move(value);
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

  const E& GetError() const noexcept {
    return *reinterpret_cast<const E*>(&_value);
  }

  constexpr bool IsOk() const noexcept {
    return GetType() == CheckedType::OK;
  }

  constexpr bool IsError() const noexcept {
    return GetType() == CheckedType::ERROR;
  }

};

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template<class E, class T>
const Checked<E, T> Error(const E &error) {
  return Checked<E, T>(CheckedType::ERROR, error);
}

template<class E, class T>
const Checked<E, T> Ok(const T &ok) {
  return Checked<E, T>(CheckedType::OK, ok);
}

template<class E, class T>
const SharedChecked<E, T> MakeSharedError(const E &error) {
  return MakeShared<Checked<E, T>>(CheckedType::ERROR, error);
}

template<class E, class T>
const SharedChecked<E, T> MakeSharedOk(const T &ok) {
  return MakeShared<Checked<E, T>>(CheckedType::OK, ok);
}

template <class E, class T, class Ef, class Of>
constexpr auto Match(const Checked<E, T>& checked, Ef error, Of ok) noexcept -> decltype(ok(checked.Get())) {
  return (checked.IsOk())
    ? ok(checked.Get())
    : error(checked.GetError());
}

template <class E, class T, class Ef, class Of>
constexpr auto Match(const SharedChecked<E, T>& checked, Ef error, Of ok) noexcept -> decltype(ok(checked->Get())) {
  return (checked->IsOk())
    ? ok(checked->Get())
    : error(checked->GetError());
}

}

#include "everest/containers/checked/traits/alternative.h"
#include "everest/containers/checked/traits/containable.h"
#include "everest/containers/checked/traits/container.h"
#include "everest/containers/checked/traits/eq.h"
#include "everest/containers/checked/traits/foldable.h"
#include "everest/containers/checked/traits/functor.h"
#include "everest/containers/checked/traits/hashable.h"
#include "everest/containers/checked/traits/monad.h"
#include "everest/containers/checked/traits/monoid.h"
#include "everest/containers/checked/traits/ord.h"
#include "everest/containers/checked/traits/semigroup.h"
#include "everest/containers/checked/traits/shows.h"
#include "everest/containers/checked/traits/unwrappable.h"
#include "everest/containers/checked/traits/zero.h"

#include "everest/containers/checked/traits/shared/alternative.h"
#include "everest/containers/checked/traits/shared/containable.h"
#include "everest/containers/checked/traits/shared/container.h"
#include "everest/containers/checked/traits/shared/eq.h"
#include "everest/containers/checked/traits/shared/foldable.h"
#include "everest/containers/checked/traits/shared/functor.h"
#include "everest/containers/checked/traits/shared/hashable.h"
#include "everest/containers/checked/traits/shared/monad.h"
#include "everest/containers/checked/traits/shared/monoid.h"
#include "everest/containers/checked/traits/shared/ord.h"
#include "everest/containers/checked/traits/shared/semigroup.h"
#include "everest/containers/checked/traits/shared/shows.h"
#include "everest/containers/checked/traits/shared/unwrappable.h"
#include "everest/containers/checked/traits/shared/zero.h"

#pragma clang diagnostic pop
