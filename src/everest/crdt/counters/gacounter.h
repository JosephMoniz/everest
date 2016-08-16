#pragma once

#include <everest/containers/map.h>
#include <everest/crdt/counters/gcounter.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/associative.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

template<class T>
class GACounter final {

  Map<String, GCounter<T>> _actors;

public:

  GACounter() noexcept : _actors() { }

  GACounter(const T& number) noexcept : _actors(number) { }

  GACounter(const GACounter<T>& other) noexcept : _actors(other._actors) { }

  GACounter(GACounter<T>&& other) noexcept : _actors(std::move(other._actors)) { }

  GACounter<T> Increment(String&& actor) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? GACounter(Put(std::move(actor), GCounter<T>(OneVal<T>::One()), _actors))
      : GACounter(Put(actor, value->Increment(), _actors));
  }

  GACounter<T> IncrementBy(String actor, const T& number) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? GACounter(Put(std::move(actor), GCounter<T>(number), _actors))
      : GACounter(Put(actor, value->IncrementBy(number), _actors));
  }

  T Value() const noexcept {
    auto result = ZeroVal<T>::Zero();
    _actors.ForEach([&](MutableMapEntry<String, GCounter<T>>& entry) {
      result = result + entry.Value().Value();
    });
  }

  GACounter<T> Add(const GACounter<T>& other) const noexcept {
    return GACounter(_actors + other._actors);
  }

  String Show() const noexcept {
    return String("GACounter(") + Shows<T>::Show(Value()) + String(")");
  }

  bool Equals(const GACounter<T>& other) const noexcept {
    return Value() == other.Value();
  }

  static GACounter<T> Zero() {
    return GACounter<T>(Map<String, GCounter<T>>());
  }

};

template<class T>
class Shows<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GACounter<T>& counter) noexcept {
    return counter.Show();
  }

};

template<class T>
class Eq<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GACounter<T>& lhs, const GACounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static GACounter<T> Zero() {
    return GACounter<T>::Zero();
  }

};

template<class T>
class Semigroup<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static GACounter<T> Add(const GACounter<T>& lhs, const GACounter<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Monoid<GACounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
