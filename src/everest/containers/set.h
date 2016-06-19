#pragma once

#include <everest/containers/mutable/mutable_set.h>

namespace everest {

template<class T>
class Set final {

  friend class Containable<Set<T>>;
  friend class Container<Set<T>>;
  friend class Filterable<Set<T>>;
  friend class Functor<Set<T>>;
  friend class Hashable<Set<T>>;
  friend class Iteration<Set<T>>;
  friend class Monad<Set<T>>;
  friend class Semigroup<Set<T>>;
  friend class Eq<Set<T>>;
  friend class Subtractable<Set<T>>;

  MutableSet<T> _wrapped;

public:

  Set() noexcept : _wrapped() { }

  Set(std::initializer_list<T> list) noexcept : _wrapped(list) { }

  Set(const Set<T>& other) = delete;

  Set(Set<T>&& other) noexcept : _wrapped(std::move(other._wrapped)) {}

  Set(MutableSet<T>&& vector) noexcept : _wrapped(std::move(vector)) { }

};

template <class T>
class Containable<Set<T>> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const Set<T>& set) noexcept {
    return Containable<MutableSet<T>>::Contains(item, set._wrapped);
  }

};

template <class T>
class Container<Set<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Set<T>& set) noexcept {
    return Container<MutableSet<T>>::Length(set._wrapped);
  }

  static constexpr bool IsEmpty(const Set<T>& set) noexcept {
    return Container<MutableSet<T>>::IsEmpty(set._wrapped);
  }

};

template <class T>
class Filterable<Set<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static Set<T> Filter(Predicate predicate, const Set<T>& set) noexcept {
    return Set<T>(Filterable<MutableSet<T>>::Filter(predicate, set._wrapped));
  }

};

template<class T>
class Functor<Set<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Set<B> Map(F f, const Set<T>& set) noexcept {
    return Set<B>(Functor<MutableSet<T>>::Map(f, set._wrapped));
  }

};

template <class T>
class Hashable<Set<T>> {
public:

  static constexpr bool exists = true;

  static int Hash(const Set<T>& set) noexcept {
    return Hashable<MutableSet<T>>::Hash(set._wrapped);
  }

};

template <class T>
class Iteration<Set<T>> {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Set<T>& container, const F& function) noexcept {
    Iteration<MutableSet<T>>::ForEach(container._wrapped, function);
  }

};

template<class T>
class Monad<Set<T>> {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr Set<B> FlatMap(F f, const Set<T>& set) noexcept {
    return Monad<MutableSet<T>>::FlatMap(f, set._wrapped);
  }

  template <class B>
  static constexpr Set<B> Then(const Set<T>& first, const Set<B>& second) noexcept {
    return second;
  }

};

template<class T>
class Monoid<Set<T>> {
public:
  static constexpr bool exists = true;
};

template<class T>
class Semigroup<Set<T>> {
public:

  static constexpr bool exists = true;

  static Set<T> Add(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return Set<T>(Semigroup<MutableSet<T>>::Add(lhs._wrapped, rhs._wrapped));
  }

};

template<class T>
class Subtractable<Set<T>> {
public:

  static constexpr bool exists = true;

  static Set<T> Subtract(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return Set<T>(Subtractable<MutableSet<T>>::Subtract(lhs._wrapped, rhs._wrapped));
  }

};

template <class T>
class Shows<Set<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const Set<T>& set) noexcept {
    auto out = String("Set(");
    ForEach(set, [&](const T& item) {
      out = out + Shows<T>::Show(item) + String(", ");
    });
    return Take(Length(out) - 2, out) + String(")");
  }

};

template<class T>
class ZeroVal<Set<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Set<T> Zero() noexcept {
    return Set<T>();
  }

};

template<class T>
class Eq<Set<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Set<T>& lhs, const Set<T>* rhs) noexcept {
    return Eq<Set<T>>::Equals(&lhs, rhs);
  }

  static bool Equals(const Set<T>* lhs, const Set<T>& rhs) noexcept {
    return Eq<Set<T>>::Equals(lhs, &rhs);
  }

  static bool Equals(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return Eq<Set<T>>::Equals(&lhs, &rhs);
  }

  static bool Equals(const Set<T>* lhs, const Set<T>* rhs) noexcept {
    return Eq<MutableSet<T>>::Equals(&lhs->_wrapped, &rhs->_wrapped);
  }

};

}