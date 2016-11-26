#pragma once

#include <stddef.h>
#include <cstdint>
#include <everest/types/int8.h>
#include <everest/memory/memory.h>
#include <everest/containers/option.h>
#include <everest/mutable_containers/mutable_vector.h>

namespace everest {

template<class T>
class Vector final {

  MutableVector<T> _wrapped;

public:

  Vector() noexcept : _wrapped() { }

  template <class U, class... U2>
  Vector(U&& element, U2&&... elements) noexcept : _wrapped(std::move(element), std::move(elements)...) { };

  Vector(const T* src, size_t length) noexcept {
    auto memory  = MutableMemory<T>(length);
    auto pointer = memory.MutablePointer();
    for (auto i = 0; i < length; i++) {
      src[i] = pointer[i];
    }
    _wrapped = MutableVector<T>(std::move(memory));
  }

  Vector(const Vector<T>& other) = delete;

  Vector(MutableVector<T>&& vector) noexcept : _wrapped(std::move(vector)) { }

  Vector(Vector<T>&& other) noexcept : _wrapped(std::move(other._wrapped)) {}

  Vector(Memory<T>&& memory) noexcept : _wrapped(std::move(memory)) { }

  Vector(MutableMemory<T>&& memory) noexcept : _wrapped(std::move(memory)) { }

  Option<const T&> At(size_t offset) const noexcept {
    if (offset < Length(_wrapped)) {
      return Option<const T&>::Some(Pointer(_wrapped)[offset]);
    } else {
      return Option<const T&>::None();
    }
  }

  const T* Pointer() const noexcept {
    return _wrapped.Pointer();
  }

  size_t Length() const noexcept {
    return _wrapped.Length();
  }

  bool IsEmpty() const noexcept {
    return _wrapped.IsEmpty();
  }

  bool Contains(const T& item) const noexcept {
    return _wrapped.Contains(item);
  }

  Vector<T> Drop(size_t length) const noexcept {
    return Vector<T>(_wrapped.Drop(length));
  }

  template<class Predicate>
  Vector<T> DropWhile(Predicate predicate) const noexcept {
    return Vector<T>(_wrapped.DropWhile(predicate));
  }

  bool Equals(const Vector<T>& other) const noexcept {
    return _wrapped.Equals(other._wrapped);
  }

  template<class Predicate>
  Vector<T> Filter(Predicate predicate) const noexcept {
    return Vector<T>(_wrapped.Filter(predicate));
  }

  T Fold() const noexcept {
    return _wrapped.Fold();
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  M FoldMap(Fn f) const noexcept {
    return _wrapped.FoldMap(f);
  }

  template <class Fn, class B>
  B FoldR(const B& init, Fn f) const noexcept {
    return _wrapped.FoldR(init, f);
  }

  template <class Fn, class B>
  B FoldL(const B& init, Fn f) const noexcept {
    return _wrapped.FoldL(init, f);
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  Vector<B> Map(F f) const noexcept {
    return Vector<B>(_wrapped.Map(f));
  }

  HashValue Hash() const noexcept {
    return _wrapped.Hash();
  }

  String ToHex() const noexcept {
    return _wrapped.ToHex();
  }

  template<class F, class B = nth_type_arg<typename std::result_of<F(T)>::type, 0>>
  Vector<B> FlatMap(F f) const noexcept {
    return Vector<B>(_wrapped.FlatMap(f));
  }

  template <class B>
  Vector<B> Then(const Vector<B>& second) const noexcept {
    return second;
  }

  Ordering Compare(const Vector<T>& other) const noexcept {
    return _wrapped.Compare(other._wrapped);
  }

  const Vector<T>& Min(const Vector<T>& rhs) const noexcept {
    return (Compare(rhs) == Ordering::GREATER)
      ? rhs
      : *this;
  }

  const Vector<T>& Max(const Vector<T>& rhs) const noexcept {
    return (Compare(rhs) == Ordering::LESS)
      ? rhs
      : *this;
  }

  Vector<T> Enqueue(const T& item) const noexcept {
    return Vector<T>(_wrapped.Enqueue(item));
  }

  Vector<T> Dequeue() const noexcept {
    return Vector<T>(_wrapped.Dequeue());
  }

  Option<const T&> Front() const noexcept {
    return _wrapped.Front();
  }

  Vector<T> Add(const Vector<T>& other) const noexcept {
    return Vector<T>(_wrapped.Add(other._wrapped));
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("Vector(")
      .Add(StringJoiner(", ").Join<Vector<T>, T>(*this))
      .Add(")")
      .Build();
  }

  Vector<T> Push(const T& item) const noexcept {
    return Vector<T>(_wrapped.Push(item));
  }

  Vector<T> Pop() const noexcept {
    return Vector<T>(_wrapped.Pop());
  }

  Option<const T&> Top() const noexcept {
    return _wrapped.Top();
  }

  Vector<T> Take(size_t length) const noexcept {
    return Vector<T>(_wrapped.Take(length));
  }

  template<class Predicate>
  Vector<T> TakeWhile(Predicate predicate) const noexcept {
    return Vector<T>(_wrapped.TakeWhile(predicate));
  }

  template <class F>
  void ForEach(const F& function) const noexcept {
    _wrapped.ForEach(function);
  }

  static Vector<T> Zero() noexcept {
    return Vector<T>();
  }

};

}
