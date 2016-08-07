#pragma once

#include <everest/containers/mutable/mutable_set.h>

namespace everest {

template<class T>
class Set final {

  MutableSet<T> _wrapped;

public:

  Set() noexcept : _wrapped() { }

  template <class U>
  Set(U&& element) noexcept : _wrapped(std::move(element)) { }

  template <class U, class... U2>
  Set(U&& element, U2&&... elements) noexcept : _wrapped(std::move(element), std::move(elements)...) { };

  Set(const Set<T>& other) = delete;

  Set(Set<T>&& other) noexcept : _wrapped(std::move(other._wrapped)) {}

  Set(MutableSet<T>&& vector) noexcept : _wrapped(std::move(vector)) { }

  bool Contains(const T& item) const noexcept {
    return _wrapped.Contains(item);
  }

  size_t Length() const noexcept {
    return _wrapped.Length();
  }

  bool IsEmpty() const noexcept {
    return _wrapped.IsEmpty();
  }

  template<class Predicate>
  Set<T> Filter(Predicate predicate) const noexcept {
    return Set<T>(_wrapped.Filter(predicate));
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  Set<B> Map(F f) const noexcept {
    return Set<B>(_wrapped.Map(f));
  }

  HashValue Hash() const noexcept {
    return _wrapped.Hash();
  }

  template <class F>
  void ForEach(const F& function) const noexcept {
    return _wrapped.ForEach(function);
  }

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  Set<B> FlatMap(F f) const noexcept {
    return Set<B>(_wrapped.FlatMap(f));
  }

  template <class B>
  Set<B> Then(const Set<B>& second) const noexcept {
    return second;
  }

  Set<T> Add(const Set<T>& other) const noexcept {
    return Set<T>(_wrapped.Add(other._wrapped));
  }

  Set<T> Subtract(const Set<T>& other) const noexcept {
    return Set<T>(_wrapped.Subtract(other));
  }

  String Show() const noexcept {
    auto out = String("Set(");
    _wrapped.ForEach([&](const T& item) {
      out = out + Shows<T>::Show(item) + String(", ");
    });
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

  bool Equals(const Set<T>& other) const noexcept {
    return _wrapped.Equals(other._wrapped);
  }

  static Set<T> Zero() noexcept {
    return Set<T>();
  }

};

template <class T>
class Containable<Set<T>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const Set<T>& set) noexcept {
    return set.Contains(item);
  }

};

template <class T>
class Container<Set<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Set<T>& set) noexcept {
    return set.Length();
  }

  static bool IsEmpty(const Set<T>& set) noexcept {
    return set.IsEmpty();
  }

};

template <class T>
class Filterable<Set<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static Set<T> Filter(Predicate predicate, const Set<T>& set) noexcept {
    return set.Filter(predicate);
  }

};

template<class T>
class Functor<Set<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Set<B> Map(F f, const Set<T>& set) noexcept {
    return set.Map(f);
  }

};

template <class T>
class Hashable<Set<T>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Set<T>& set) noexcept {
    return set.Hash();
  }

};

template <class T>
class Iteration<Set<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Set<T>& container, const F& function) noexcept {
    return container.ForEach(function);
  }

};

template<class T>
class Monad<Set<T>> final {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static Set<B> FlatMap(F f, const Set<T>& set) noexcept {
    return set.FlatMap(f);
  }

  template <class B>
  static Set<B> Then(const Set<T>& first, const Set<B>& second) noexcept {
    return first.Then(second);
  }

};

template<class T>
class Monoid<Set<T>> final {
public:

  static constexpr bool exists = true;

};

template<class T>
class Semigroup<Set<T>> final {
public:

  static constexpr bool exists = true;

  static Set<T> Add(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Subtractable<Set<T>> final {
public:

  static constexpr bool exists = true;

  static Set<T> Subtract(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

template <class T>
class Shows<Set<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Set<T>& set) noexcept {
    return set.Show();
  }

};

template<class T>
class ZeroVal<Set<T>> final {
public:

  static constexpr bool exists = true;

  static Set<T> Zero() noexcept {
    return Set<T>::Zero();
  }

};

template<class T>
class Eq<Set<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}