#pragma once

#include <everest/mutable_containers/mutable_set.h>

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

  template<class F, class B = nth_type_arg<typename std::result_of<F(T)>::type, 0>>
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

  Set<T> Intersect(const Set<T>& other) const noexcept {
    return Set<T>(_wrapped.Intersect(other._wrapped));
  }

  Set<T> Subtract(const Set<T>& other) const noexcept {
    return Set<T>(_wrapped.Subtract(other._wrapped));
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("Set(")
      .Add(StringJoiner(", ").Join<Set<T>, T>(*this))
      .Add(")")
      .Build();
  }

  bool Equals(const Set<T>& other) const noexcept {
    return _wrapped.Equals(other._wrapped);
  }

  static Set<T> Zero() noexcept {
    return Set<T>();
  }

};

}