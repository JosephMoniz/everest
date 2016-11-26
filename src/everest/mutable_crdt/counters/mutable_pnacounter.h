#pragma once

#include <everest/traits/unlawful/associative.h>
#include <everest/traits/unlawful/container.h>
#include <everest/strings/string.h>
#include <everest/mutable_containers/mutable_map.h>
#include <everest/mutable_crdt/counters/mutable_pncounter.h>

namespace everest {

template <class A, class T, template <class, class> class InnerMapType = MutableSortedVectorMap>
class MutablePNACounter final {

  using Self = MutablePNACounter<A, T>;

  using OptionalCounter = Option<MutablePNCounter<T>*>;

  using InnerCounter = MutablePNCounter<T>;

  using InnerMap = InnerMapType<A, MutablePNCounter<T>>;

  using InnerMapEntry = MutableMapEntry<A, MutablePNCounter<T>>;

  A _actorIdentifier;

  InnerMap _actors;

public:

  MutablePNACounter(A&& actorIdentifier) noexcept : _actorIdentifier(std::move(actorIdentifier)),
                                                    _actors() { }

  MutablePNACounter(A&& actorIdentifier, InnerMap&& actors) noexcept : _actorIdentifier(std::move(actorIdentifier)),
                                                                       _actors(std::move(actors)) { }

  MutablePNACounter(A&& actorIdentifier, const T& number) noexcept : _actorIdentifier(std::move(actorIdentifier)) {
    _actors.PutInPlace(Copyable<A>::Copy(actorIdentifier), InnerCounter(number));
  }

  Self Copy() const noexcept {
    return Self(Copyable<T>::Copy(_actorIdentifier), _actors.Copy());
  }

  Self& Increment() noexcept {
    return IncrementBy(OneVal<T>::One());
  }

  Self& IncrementBy(const T& number) noexcept {
    OptionalCounter value = _actors.GetInPlace(_actorIdentifier);
    if (IsEmpty(value)) {
      _actors.PutInPlace(Copyable<A>::Copy(_actorIdentifier), InnerCounter(OneVal<T>::One()));
      return *this;
    } else {
      value.GetMutable()->IncrementBy(number);
      return *this;
    }
  }

  Self& Decrement() noexcept {
    return DecrementBy(OneVal<T>::One());
  }

  Self& DecrementBy(const T& number) noexcept {
    OptionalCounter value = _actors.GetInPlace(_actorIdentifier);
    if (IsEmpty(value)) {
      _actors.PutInPlace(Copyable<A>::Copy(_actorIdentifier), InnerCounter(Negate(OneVal<T>::One())));
      return *this;
    } else {
      value.GetMutable()->DecrementBy(number);
      return *this;
    }
  }

  T Value() const noexcept {
    auto result = ZeroVal<T>::Zero();
    _actors.ForEach([&](const InnerMapEntry& entry) {
      result = result + entry.ConstValue().Value();
    });
    return result;
  }

  Self Add(const Self& other) const noexcept {
    return Self(Copyable<A>::Copy(_actorIdentifier), _actors + other._actors);
  }

  Self& AddInPlace(const Self& other) noexcept {
    _actors.AddInPlace(other._actors);
    return *this;
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutablePNACounter(")
      .Add(Shows<T>::Show(Value()))
      .Add(")")
      .Build();
  }

  bool Equals(const Self& rhs) const noexcept {
    return Value() == rhs.Value();
  }

  /*
  static MutablePositiveNegativeActorCounter<A, T> Zero() {
    return MutablePositiveNegativeActorCounter<A, T>();
  }
   */

};

}
