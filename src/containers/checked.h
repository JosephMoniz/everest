#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_CONTAINERS_CHECKED_H
#define TRAITOROUS_CONTAINERS_CHECKED_H

#include <type_traits>
#include <meta/max.h>
#include <string>
#include <traits/unlawful/ord.h>
#include <meta/nth_arg.h>

#include "traits/unlawful/container.h"

#include "containers/shared.h"

namespace traitorous {

enum class CheckedType {
  OK,
  ERROR
};

template<class E, class T>
class LocalChecked {


  using data_t = typename std::aligned_storage<
    meta_max<sizeof(E), sizeof(T)>::value,
    meta_max<alignof(E), alignof(T)>::value
  >::type;

  const CheckedType _tag;

  data_t _value;

public:

  LocalChecked(const CheckedType& tag, const T& o) noexcept : _tag(tag) {
    new (&_value) T(o);
  }

  LocalChecked(const CheckedType& tag, const E& o) noexcept : _tag(tag) {
    new (&_value) E(o);
  }

  ~LocalChecked() noexcept {
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
using Checked = Shared<LocalChecked<E, T>>;

template<class E, class T>
const LocalChecked<E, T> LocalError(const E& error) {
  return LocalChecked<E, T>(CheckedType::ERROR, error);
}

template<class E, class T>
const LocalChecked<E, T> LocalOk(const T& ok) {
  return LocalChecked<E, T>(CheckedType::OK, ok);
}

template<class E, class T>
const Checked<E, T> Error(const E& error) {
  return MakeShared<LocalChecked<E, T>>(CheckedType::ERROR, error);
}

template<class E, class T>
const Checked<E, T> Ok(const T& ok) {
  return MakeShared<LocalChecked<E, T>>(CheckedType::OK, ok);
}

template <class E, class T, class Ef, class Of>
constexpr auto Match(const LocalChecked<E, T>& checked, Ef error, Of ok) noexcept -> decltype(ok(checked.Get())) {
  return (checked.GetType() == CheckedType::OK)
    ? ok(checked.Get())
    : error(checked.GetError());
}

template <class E, class T, class Ef, class Of>
constexpr auto Match(const Checked<E, T>& checked, Ef error, Of ok) noexcept -> decltype(ok(checked->Get())) {
  return (checked->GetType() == CheckedType::OK)
    ? ok(checked->Get())
    : error(checked->GetError());
}

template <class E, class T>
class Shows<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const LocalChecked<E, T>& n) noexcept {
    return Match(n,
      [](const E& error) { return std::string("LocalError(") + Shows<E>::Show(error) + ")"; },
      [](const T& ok)    { return std::string("LocalOk(") + Shows<T>::Show(ok) + ")"; }
    );
  }

};

template <class E, class T>
class Eq<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const LocalChecked<E, T>& lhs, const LocalChecked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& errorLeft){
        return Match(rhs,
          [&](const E& errorRight) { return errorLeft == errorRight; },
          [](const T& okRight)     { return false; }
        );
      },
      [&](const T& okLeft){
        return Match(rhs,
          [](const E& errorLeft)   { return false; },
          [&](const T& okRight)    { return okLeft == okRight; }
        );
      }
  );
}

};

template<class E, class T>
class Ord<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const LocalChecked<E, T> &lhs,
                                    const LocalChecked<E, T> &rhs) noexcept
  {
    return Match(lhs,
      [&](const E& errorLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return traitorous::Compare(errorLeft, errorRight); },
          [](const T &ok)          { return LESS; }
        );
      },
      [&](const T &okLeft) {
        return Match(rhs,
          [](const E& error)    { return GREATER; },
          [&](const T &okRight) { return traitorous::Compare(okLeft, okRight); }
        );
      }
    );
  }

  static constexpr const LocalChecked<E, T>& Min(const LocalChecked<E, T> &lhs,
                                                 const LocalChecked<E, T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const LocalChecked<E, T>& Max(const LocalChecked<E, T> &lhs,
                                                 const LocalChecked<E, T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

};

template <class E, class T>
class Containable<LocalChecked<E, T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& item, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error)   { return false; },
      [&item](const T& ok) { return item == ok; }
    );
  }

};

template <class E, class T>
class Container<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return 0u; },
      [](const T& ok)    { return 1u; }
    );
  }

  static constexpr bool IsEmpty(const LocalChecked<E, T>& o) noexcept {
    return Match(o,
      [](const E& error) { return true; },
      [](const T& ok)    { return false; }
    );
  }

};

template <class E, class T>
class Functor<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr LocalChecked<E, B> Map(F f, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return LocalError<E, B>(error); },
      [&](const T& ok)    { return LocalOk<E, B>(f(ok)); }
    );
  }

};

template <class E, class T>
class Alternative<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalChecked<E, T> Alt(const LocalChecked<E, T>& lhs,
                                          const LocalChecked<E, T>& rhs) noexcept
  {
    return Match(lhs,
      [&rhs](const E& error) { return rhs; },
      [&lhs](const T& ok)    { return lhs; }
    );
  }

};

template <class E, class T>
class Monad<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 1>>
  static constexpr LocalChecked<E, B> FlatMap(F f, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return LocalError<E, B>(error); },
      [&](const T& ok)    { return f(ok); }
    );
  }

  template <class B>
  static constexpr LocalChecked<E, B> Then(const LocalChecked<E, T>& m, const LocalChecked<E, B>& n) noexcept {
    return Match(m,
      [&](const E& error) { return m; },
      [&](const T& ok)    { return n; }
    );
  }

};

template <class E, class T>
class Semigroup<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalChecked<E, T> Add(const LocalChecked<E, T>& lhs, const LocalChecked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& errorLeft) { return lhs; },
      [&](const T& okLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return rhs; },
          [&](const T& okRight)    { return LocalOk<E, T>(okLeft + okRight); }
        );
      }
    );
  }

};

template <class E, class T>
class ZeroVal<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalChecked<E, T> Zero() {
    return LocalOk<E, T>(ZeroVal<T>::Zero());
  }

};

template <class E, class T>
class Monoid<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

};

template <class E, class T>
class Hashable<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const LocalChecked<E, T>& o) noexcept {
    return Match(o,
      [](const E& error) { return Hashable<E>::Hash(error); },
      [](const T& ok)    { return Hashable<T>::Hash(ok); }
    );
  }

};

template <class E, class T>
class Foldable<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return ZeroVal<T>::Zero(); },
      [&](const T& ok)   { return ok; }
    );
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return ZeroVal<M>::Zero(); },
      [&](const T& ok)   { return f(ok); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f, const B& init, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return init; },
      [&](const T& ok)    { return f(init, ok); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f, const B& init, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return init; },
      [&](const T& ok)    { return f(init, ok); }
    );
  }

};

template <class E, class T>
class Unwrappable<LocalChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return d(); },
      [](const T& ok)     { return ok; }
    );
  }

  static constexpr T GetOrDefault(const T& d, const LocalChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return d; },
      [](const T& ok)     { return ok; }
    );
  }

};

template <class E, class T>
class Shows<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const Checked<E, T>& n) noexcept {
    return Match(n,
      [](const E& error) { return std::string("Error(") + Shows<E>::Show(error) + ")"; },
      [](const T& ok)    { return std::string("Ok(") + Shows<T>::Show(ok) + ")"; }
    );
  }

};

template <class E, class T>
class Eq<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return Eq<LocalChecked<E, T>>::Equals(*lhs, *rhs);
  }

};

template<class E, class T>
class Ord<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const Checked<E, T> &lhs, const Checked<E, T> &rhs) noexcept {
    return Ord<LocalChecked<E, T>>::Compare(*lhs, *rhs);
  }

  static constexpr const Checked<E, T>& Min(const Checked<E, T> &lhs, const Checked<E, T> &rhs) noexcept {
    return (Compare(lhs, rhs) == GREATER)
       ? rhs
       : lhs;
  }

  static constexpr const Checked<E, T>& Max(const Checked<E, T> &lhs, const Checked<E, T> &rhs) noexcept {
    return (Compare(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

};

template <class E, class T>
class Containable<Checked<E, T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& item, const Checked<E, T>& checked) noexcept {
    return Containable<LocalChecked<E, T>, T>::Contains(item, *checked);
  }

};

template <class E, class T>
class Container<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Checked<E, T>& checked) noexcept {
    return Container<LocalChecked<E, T>>::Length(*checked);
  }

  static constexpr bool IsEmpty(const Checked<E, T>& checked) noexcept {
    return Container<LocalChecked<E, T>>::IsEmpty(*checked);
  }

};

template <class E, class T>
class Functor<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr Checked<E, B> Map(F f, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return Error<E, B>(error); },
      [&](const T& ok)    { return Ok<E, B>(f(ok)); }
    );
  }

};

template <class E, class T>
class Alternative<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Checked<E, T> Alt(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&rhs](const E& error) { return rhs; },
      [&lhs](const T& ok)    { return lhs; }
    );
  }

};

template <class E, class T>
class Monad<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<nth_arg<typename std::result_of<F(T)>::type, 0>, 1>>
  static constexpr Checked<E, B> FlatMap(F f, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return Error<E, B>(error); },
      [&](const T& ok)    { return f(ok); }
    );
  }

  template <class B>
  static constexpr Checked<E, B> Then(const Checked<E, T>& m, const Checked<E, B>& n) noexcept {
    return Match(m,
      [&](const E& error) { return m; },
      [&](const T& ok)    { return n; }
    );
  }

};

template <class E, class T>
class Semigroup<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Checked<E, T> Add(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& errorLeft) { return lhs; },
      [&](const T& okLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return rhs; },
          [&](const T& okRight)    { return Ok<E, T>(okLeft + okRight); }
        );
      }
    );
  }

};

template <class E, class T>
class ZeroVal<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Checked<E, T> Zero() {
    return Ok<E, T>(ZeroVal<T>::Zero());
  }

};

template <class E, class T>
class Monoid<Checked<E, T>> {
public:

  static constexpr bool exists = true;

};

template <class E, class T>
class Hashable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const Checked<E, T>& checked) noexcept {
    return Hashable<LocalChecked<E, T>>::Hash(*checked);
  }

};

template <class E, class T>
class Foldable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Checked<E, T>& checked) noexcept {
    return Foldable<LocalChecked<E, T>>::Fold(*checked);
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Checked<E, T>& checked) noexcept {
    return Foldable<LocalChecked<E, T>>::FoldMap(f, *checked);
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return Foldable<LocalChecked<E, T>>::FoldR(f, init, *checked);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return Foldable<LocalChecked<E, T>>::FoldL(f, init, *checked);
  }

};

template <class E, class T>
class Unwrappable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const Checked<E, T>& checked) noexcept {
    return Unwrappable<LocalChecked<E, T>>::GetOrElse(d, *checked);
  }

  static constexpr T GetOrDefault(const T& d, const Checked<E, T>& checked) noexcept {
    return Unwrappable<LocalChecked<E, T>>::GetOrDefault(d, *checked);
  }

};

}

#endif

#pragma clang diagnostic pop
