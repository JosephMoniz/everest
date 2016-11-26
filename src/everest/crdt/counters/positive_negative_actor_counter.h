#pragma once

#include <everest/containers/map.h>
#include <everest/crdt/counters/postivie_negative_counter.h>
#include <everest/strings/string.h>
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
class PositiveNegativeActorCounter final {

  Map<String, PositiveNegativeCounter<T>> _actors;

public:

  PositiveNegativeActorCounter() noexcept : _actors() { }

  PositiveNegativeActorCounter(Map<String, PositiveNegativeCounter<T>>&& actors) noexcept : _actors(std::move(actors)) { }

  PositiveNegativeActorCounter<T> Increment(String&& actor) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PositiveNegativeActorCounter(Put(std::move(actor), PositiveNegativeCounter<T>(OneVal<T>::One()), _actors))
      : PositiveNegativeActorCounter(Put(actor, value->Increment(), _actors));
  }

  PositiveNegativeActorCounter<T> IncrementBy(String&& actor, const T& number) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PositiveNegativeActorCounter(Put(std::move(actor), PositiveNegativeCounter<T>(number), _actors))
      : PositiveNegativeActorCounter(Put(actor, value->IncrementBy(number), _actors));
  }

  PositiveNegativeActorCounter<T> Decrement(String&& actor) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PositiveNegativeActorCounter(Put(std::move(actor), PositiveNegativeCounter<T>().Decrement(), _actors))
      : PositiveNegativeActorCounter(Put(actor, value->Decrement(), _actors));
  }

  PositiveNegativeActorCounter<T> DecrementBy(String&& actor, const T& number) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PositiveNegativeActorCounter(Put(std::move(actor), PositiveNegativeCounter<T>().DecrementBy(number), _actors))
      : PositiveNegativeActorCounter(Put(actor, value->DecrementBy(number), _actors));
  }

  T Value() const noexcept {
    auto result = ZeroVal<T>::Zero();
    _actors.ForEach([&](MutableMapEntry<String, PositiveNegativeActorCounter<T>>& entry) {
      result = result + entry.Value().Value();
    });
  }

  PositiveNegativeActorCounter<T> Add(const PositiveNegativeActorCounter<T>& other) const noexcept {
    return PositiveNegativeActorCounter(_actors + other._actors);
  }

  String Show() const noexcept {
    return String("PNACounter(") + Shows<T>::Show(Value()) + String(")");
  }

  bool Equals(const PositiveNegativeActorCounter<T>& rhs) const noexcept {
    return Value() == rhs.Value();
  }

  static PositiveNegativeActorCounter<T> Zero() {
    return PositiveNegativeActorCounter<T>(Map<String, PositiveNegativeCounter<T>>());
  }

};

template<class T>
class Shows<PositiveNegativeActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const PositiveNegativeActorCounter<T>& counter) noexcept {
    return counter.Show();
  }

};

template<class T>
class Eq<PositiveNegativeActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const PositiveNegativeActorCounter<T>& lhs, const PositiveNegativeActorCounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<PositiveNegativeActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static PositiveNegativeActorCounter<T> Zero() {
    return PositiveNegativeActorCounter<T>::Zero();
  }

};

template<class T>
class Semigroup<PositiveNegativeActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static PositiveNegativeActorCounter<T> Add(const PositiveNegativeActorCounter<T>& lhs, const PositiveNegativeActorCounter<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Monoid<PositiveNegativeActorCounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
