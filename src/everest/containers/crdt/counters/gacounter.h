#pragma once

#include <everest/containers/map.h>
#include <everest/containers/crdt/counters/gcounter.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/associative.h>

namespace everest {

template<class T>
class GACounter final {

  friend class Semigroup<GACounter<T>>;

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
    ForEach(_actors, [&](MutableMapEntry<String, T>& entry) {
      result = result + entry.Value().Value();
    });
  }

};

template<class T>
class Shows<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GACounter<T>& counter) noexcept {
    return String("GACounter(") + Shows<T>::Show(counter.Value()) + String(")");
  }

};

template<class T>
class Eq<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GACounter<T>& lhs, const GACounter<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr GACounter<T> Zero() {
    return GACounter(Map());
  }

};

template<class T>
class Semigroup<GACounter<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr GACounter<T> Add(const GACounter<T>& lhs, const GACounter<T>& rhs) noexcept {
    return GACounter(lhs._actors + rhs._actors);
  }

};

template<class T>
class Monoid<GACounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
