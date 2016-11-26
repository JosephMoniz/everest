#pragma once

#include <everest/containers/map.h>
#include <everest/crdt/counters/grow_only_counter.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/associative.h>
#include <everest/traits/unlawful/one.h>
#include <everest/mutable_containers/sorted_vector_map/container.h>

namespace everest {

template<class T>
class GrowOnlyActorCounter final {

  Map<String, GrowOnlyCounter<T>> _actors;

public:

  GrowOnlyActorCounter() noexcept : _actors() { }

  GrowOnlyActorCounter(const T& number) noexcept : _actors(number) { }

  GrowOnlyActorCounter(const GrowOnlyActorCounter<T>& other) noexcept : _actors(other._actors) { }

  GrowOnlyActorCounter(GrowOnlyActorCounter<T>&& other) noexcept : _actors(std::move(other._actors)) { }

  GrowOnlyActorCounter<T> Increment(String&& actor) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? GrowOnlyActorCounter(Put(std::move(actor), GrowOnlyCounter<T>(OneVal<T>::One()), _actors))
      : GrowOnlyActorCounter(Put(actor, value->Increment(), _actors));
  }

  GrowOnlyActorCounter<T> IncrementBy(String actor, const T& number) const noexcept {
    auto value = Get(actor, _actors);
    return (value.IsEmpty())
      ? GrowOnlyActorCounter(Put(std::move(actor), GrowOnlyCounter<T>(number), _actors))
      : GrowOnlyActorCounter(Put(actor, value->IncrementBy(number), _actors));
  }

  T Value() const noexcept {
    auto result = ZeroVal<T>::Zero();
    _actors.ForEach([&](MutableMapEntry<String, GrowOnlyCounter<T>>& entry) {
      result = result + entry.Value().Value();
    });
  }

  GrowOnlyActorCounter<T> Add(const GrowOnlyActorCounter<T>& other) const noexcept {
    return GrowOnlyActorCounter(_actors + other._actors);
  }

  String Show() const noexcept {
    return String("GACounter(") + Shows<T>::Show(Value()) + String(")");
  }

  bool Equals(const GrowOnlyActorCounter<T>& other) const noexcept {
    return Value() == other.Value();
  }

  static GrowOnlyActorCounter<T> Zero() {
    return GrowOnlyActorCounter<T>(Map<String, GrowOnlyCounter<T>>());
  }

};

template<class T>
class Shows<GrowOnlyActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GrowOnlyActorCounter<T>& counter) noexcept {
    return counter.Show();
  }

};

template<class T>
class Eq<GrowOnlyActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GrowOnlyActorCounter<T>& lhs, const GrowOnlyActorCounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<GrowOnlyActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static GrowOnlyActorCounter<T> Zero() {
    return GrowOnlyActorCounter<T>::Zero();
  }

};

template<class T>
class Semigroup<GrowOnlyActorCounter<T>> final {
public:

  static constexpr bool exists = true;

  static GrowOnlyActorCounter<T> Add(const GrowOnlyActorCounter<T>& lhs, const GrowOnlyActorCounter<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Monoid<GrowOnlyActorCounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
