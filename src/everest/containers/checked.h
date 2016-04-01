#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/types/string.h>
#include <everest/meta/max.h>
#include <everest/meta/nth_arg.h>
#include <everest/containers/shared.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/traits/lawful/alternative.h>
#include <everest/traits/lawful/monad.h>
#include <everest/traits/unlawful/unwrappable.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/lawful/foldable.h>
#include <everest/traits/unlawful/zero.h>

namespace traitorous {

enum class CheckedType {
  OK,
  ERROR
};

template<>
class Shows<CheckedType> {
public:

  static constexpr bool exists = true;

  static String Show(CheckedType n) noexcept {
    switch(n) {
      case CheckedType::OK:    return String("OK");
      case CheckedType::ERROR: return String("ERROR");
    }
  }

};

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

template <class E, class T>
class Shows<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const Checked<E, T>& n) noexcept {
    return Match(n,
      [](const E& error) { return String("Error(") + Shows<E>::Show(error) + String(")"); },
      [](const T& ok)    { return String("Ok(") + Shows<T>::Show(ok) + String(")"); }
    );
  }

};

template <class E, class T>
class Eq<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
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
class Ord<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const Checked<E, T> &lhs,
                                    const Checked<E, T> &rhs) noexcept
  {
    return Match(lhs,
      [&](const E& errorLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return traitorous::Compare(errorLeft, errorRight); },
          [](const T &ok)          { return Ordering::LESS; }
        );
      },
      [&](const T &okLeft) {
        return Match(rhs,
          [](const E& error)    { return Ordering::GREATER; },
          [&](const T &okRight) { return traitorous::Compare(okLeft, okRight); }
        );
      }
    );
  }

  static constexpr const Checked<E, T>& Min(const Checked<E, T> &lhs,
                                            const Checked<E, T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const Checked<E, T>& Max(const Checked<E, T> &lhs,
                                            const Checked<E, T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

template <class E, class T>
class Containable<Checked<E, T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& item, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error)   { return false; },
      [&item](const T& ok) { return item == ok; }
    );
  }

};

template <class E, class T>
class Container<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return 0u; },
      [](const T& ok)    { return 1u; }
    );
  }

  static constexpr bool IsEmpty(const Checked<E, T>& o) noexcept {
    return Match(o,
      [](const E& error) { return true; },
      [](const T& ok)    { return false; }
    );
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

  static constexpr Checked<E, T> Alt(const Checked<E, T>& lhs,
                                     const Checked<E, T>& rhs) noexcept
  {
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

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 1>>
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

  static constexpr int Hash(const Checked<E, T>& o) noexcept {
    return Match(o,
      [](const E& error) { return Hashable<E>::Hash(error); },
      [](const T& ok)    { return Hashable<T>::Hash(ok); }
    );
  }

};

template <class E, class T>
class Foldable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return ZeroVal<T>::Zero(); },
      [&](const T& ok)   { return ok; }
    );
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return ZeroVal<M>::Zero(); },
      [&](const T& ok)   { return f(ok); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return init; },
      [&](const T& ok)    { return f(init, ok); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return init; },
      [&](const T& ok)    { return f(init, ok); }
    );
  }

};

template <class E, class T>
class Unwrappable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return d(); },
      [](const T& ok)     { return ok; }
    );
  }

  static constexpr T GetOrDefault(const T& d, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return d; },
      [](const T& ok)     { return ok; }
    );
  }

};

template <class E, class T>
class Shows<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const SharedChecked<E, T>& n) noexcept {
    return Match(n,
      [](const E& error) { return String("SharedError(") + Shows<E>::Show(error) + String(")"); },
      [](const T& ok)    { return String("SharedOk(") + Shows<T>::Show(ok) + String(")"); }
    );
  }

};

template <class E, class T>
class Eq<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const SharedChecked<E, T>& lhs, const SharedChecked<E, T>& rhs) noexcept {
    return Eq<Checked<E, T>>::Equals(*lhs, *rhs);
  }

};

template<class E, class T>
class Ord<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const SharedChecked<E, T> &lhs, const SharedChecked<E, T> &rhs) noexcept {
    return Ord<Checked<E, T>>::Compare(*lhs, *rhs);
  }

  static constexpr const SharedChecked<E, T>& Min(const SharedChecked<E, T> &lhs, const SharedChecked<E, T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
       ? rhs
       : lhs;
  }

  static constexpr const SharedChecked<E, T>& Max(const SharedChecked<E, T> &lhs, const SharedChecked<E, T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

template <class E, class T>
class Containable<SharedChecked<E, T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& item, const SharedChecked<E, T>& checked) noexcept {
    return Containable<Checked<E, T>, T>::Contains(item, *checked);
  }

};

template <class E, class T>
class Container<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const SharedChecked<E, T>& checked) noexcept {
    return Container<Checked<E, T>>::Length(*checked);
  }

  static constexpr bool IsEmpty(const SharedChecked<E, T>& checked) noexcept {
    return Container<Checked<E, T>>::IsEmpty(*checked);
  }

};

template <class E, class T>
class Functor<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr SharedChecked<E, B> Map(F f, const SharedChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return MakeSharedError<E, B>(error); },
      [&](const T& ok)    { return MakeSharedOk<E, B>(f(ok)); }
    );
  }

};

template <class E, class T>
class Alternative<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedChecked<E, T> Alt(const SharedChecked<E, T>& lhs, const SharedChecked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& error) { return rhs; },
      [&](const T& ok)    { return lhs; }
    );
  }

};

template <class E, class T>
class Monad<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<nth_arg<typename std::result_of<F(T)>::type, 0>, 1>>
  static constexpr SharedChecked<E, B> FlatMap(F f, const SharedChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return MakeSharedError<E, B>(error); },
      [&](const T& ok)    { return f(ok); }
    );
  }

  template <class B>
  static constexpr SharedChecked<E, B> Then(const SharedChecked<E, T>& m, const SharedChecked<E, B>& n) noexcept {
    return Match(m,
      [&](const E& error) { return m; },
      [&](const T& ok)    { return n; }
    );
  }

};

template <class E, class T>
class Semigroup<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedChecked<E, T> Add(const SharedChecked<E, T>& lhs, const SharedChecked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& errorLeft) { return lhs; },
      [&](const T& okLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return rhs; },
          [&](const T& okRight)    { return MakeSharedOk<E, T>(okLeft + okRight); }
        );
      }
    );
  }

};

template <class E, class T>
class ZeroVal<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedChecked<E, T> Zero() {
    return MakeSharedOk<E, T>(ZeroVal<T>::Zero());
  }

};

template <class E, class T>
class Monoid<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

};

template <class E, class T>
class Hashable<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const SharedChecked<E, T>& checked) noexcept {
    return Hashable<Checked<E, T>>::Hash(*checked);
  }

};

template <class E, class T>
class Foldable<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::Fold(*checked);
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::FoldMap(f, *checked);
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f, const B& init, const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::FoldR(f, init, *checked);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f, const B& init, const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::FoldL(f, init, *checked);
  }

};

template <class E, class T>
class Unwrappable<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const SharedChecked<E, T>& checked) noexcept {
    return Unwrappable<Checked<E, T>>::GetOrElse(d, *checked);
  }

  static constexpr T GetOrDefault(const T& d, const SharedChecked<E, T>& checked) noexcept {
    return Unwrappable<Checked<E, T>>::GetOrDefault(d, *checked);
  }

};

}

#pragma clang diagnostic pop
