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

  Checked() noexcept : _tag(CheckedType::UNINITIALIZED), _value() { }

  template <class U = T>
  Checked(const CheckedType& tag,
          const T value,
          typename std::enable_if<Fundamental<U>::exists>::type* = 0) noexcept : _tag(tag)
  {
    new (&_value) T(value);
  }

  Checked(const CheckedType& tag, T&& value) noexcept : _tag(tag) {
    new (&_value) T(std::move(value));
  }

  template <class U = E>
  Checked(const CheckedType& tag,
          const E value,
          typename std::enable_if<Fundamental<U>::exists>::type* = 0) noexcept : _tag(tag)
  {
    new (&_value) E(value);
  }

  Checked(const CheckedType& tag, E&& value) noexcept : _tag(tag) {
    new (&_value) E(std::move(value));
  }

  /*

  Checked(const Checked<E, T>& other) = delete;

  Checked(Checked<E, T>&& other) noexcept : _tag(other._tag) {
    other._tag = CheckedType::UNINITIALIZED;
    switch (other._tag) {
      case CheckedType::OK:
        other._value = std::move(*reinterpret_cast<T*>((data_t*)&_value));
        break;
      case CheckedType::ERROR:
        other._value = std::move(*reinterpret_cast<E*>((data_t*)&_value));
        break;
      case CheckedType::UNINITIALIZED:
        break;
    }
  }
   */

  ~Checked() noexcept {
    if (_tag == CheckedType::OK) {
      reinterpret_cast<T*>(&_value)->~T();
    } else {
      reinterpret_cast<E*>(&_value)->~E();
    }
  }

  static Checked<E, T> Error(const E& error) noexcept {
    return Checked<E, T>(CheckedType::ERROR, error);
  }

  static Checked<E, T> Error(E&& error) noexcept {
    return Checked<E, T>(CheckedType::ERROR, std::forward<E>(error));
  }


  static Checked<E, T> Ok(const T& ok) noexcept {
    return Checked<E, T>(CheckedType::OK, ok);
  }

  static Checked<E, T> Ok(T&& ok) noexcept {
    return Checked<E, T>(CheckedType::OK, std::forward<T>(ok));
  }

  CheckedType GetType() const noexcept {
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

  bool IsOk() const noexcept {
    return GetType() == CheckedType::OK;
  }

  bool IsError() const noexcept {
    return GetType() == CheckedType::ERROR;
  }

  const Checked<E, T>& Alt(const Checked<E, T>& other) const noexcept {
    return IsOk()
      ? *this
      : other;
  }

  bool Contains(const T& item) const noexcept {
    return IsOk()
      ? item == Get()
      : false;
  }

  size_t Length() const noexcept {
    return IsOk()
      ? 1
      : 0;
  }

  bool IsEmpty() const noexcept {
    return IsError();
  }

  bool Equals(const Checked <E, T>& rhs) const noexcept {
    if (IsOk()) {
      return rhs.IsOk() && Get() == rhs.Get();
    } else {
      return !rhs.IsOk() && GetError() == rhs.GetError();
    }
  }

  T Fold() const noexcept {
    return IsOk()
      ? Get()
      : ZeroVal<T>::Zero();
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  M FoldMap(Fn f) const noexcept {
    return IsOk()
      ? f(Get())
      : ZeroVal<T>::Zero();
  }

  template <class Fn, class B>
  B FoldR(const B& init, Fn f) const noexcept {
    return IsOk()
      ? f(init, Get())
      : ZeroVal<T>::Zero();
  }

  template <class Fn, class B>
  B FoldL(const B& init, Fn f) const noexcept {
    return IsOk()
      ? f(init, Get())
      : ZeroVal<T>::Zero();
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  Checked<E, B> Map(F f) const noexcept {
    return IsOk()
      ? Checked<E, B>::Ok(f(Get()))
      : Checked<E, B>::Error(GetError());
  }

  HashValue Hash() const noexcept {
    return IsOk()
      ? Hashable<T>::Hash(Get())
      : Hashable<E>::Hash(GetError());
  }

  template <class F, class B = nth_type_arg<typename std::result_of<F(T)>::type, 1>>
  Checked<E, B> FlatMap(F f) const noexcept {
    return IsOk()
      ? f(Get())
      : Checked<E, B>::Error(GetError());
  }

  template <class B>
  const Checked<E, B>& Then(const Checked<E, B>& other) const noexcept {
    return IsOk()
      ? other
      : *this;
  }

  Ordering Compare(const Checked<E, T>& other) const noexcept {
    if (IsOk()) {
      if (other.IsOk()) {
        return Ord<T>::Compare(Get(), other.Get());
      } else {
        return Ordering::GREATER;
      }
    } else {
      if (other.IsOk()) {
        return Ordering::LESS;
      } else {
        return Ord<E>::Compare(GetError(), other.GetError());
      }
    }
  }

  const Checked<E, T>& Min(const Checked<E, T>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const Checked<E, T>& Max(const Checked<E, T>& other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  Checked<E, T> Add(const Checked<E, T>& other) const noexcept {
    if (IsOk()) {
      if (other.IsOk()) {
        return Checked<E, T>::Ok(Get() + other.Get());
      } else {
        return other;
      }
    } else {
      return *this;
    }
  }

  String Show() const noexcept {
    if (IsOk()) {
      return String::Builder()
        .Add("Ok(")
        .Add(Shows<T>::Show(Get()))
        .Add(")")
        .Build();
    } else {
      return String::Builder()
        .Add("Error(")
        .Add(Shows<E>::Show(GetError()))
        .Add(")")
        .Build();
    }
  }

  template <class F>
  T GetOrElse(F alternative) const noexcept {
    return IsOk()
      ? Get()
      : alternative();
  }

  const T& GetOrDefault(const T& alternative) const noexcept {
    return IsOk()
      ? Get()
      : alternative;
  }

  template <class Ef, class Of>
  auto Match(Ef error, Of ok) const noexcept -> decltype(ok(Get())) {
    return (IsOk())
      ? ok(Get())
      : error(GetError());
  }

  template <class Ef, class Of>
  auto MatchWithMove(Ef error, Of ok) const noexcept -> decltype(ok(GetMovable())) {
    return (IsOk())
      ? ok(GetMovable())
      : error(GetMovableError());
  }

  static Checked<E, T> Zero() {
    return Checked<E, T>::Ok(ZeroVal<T>::Zero());
  }

};

}

#pragma clang diagnostic pop
