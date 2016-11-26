#pragma once

#include <utility>
#include <everest/mutable_containers/mutable_tuple.h>

namespace everest {

template<class K, class V>
class MutableMapEntry final {

  MutableTuple<K, V> _wrapped;

public:

  MutableMapEntry() : _wrapped() {}

  MutableMapEntry(K&& key, V&& value) noexcept : _wrapped(std::move(key), std::move(value)) { }

  MutableMapEntry(MutableMapEntry<K, V>&& other) noexcept : _wrapped(std::move(other._wrapped)) { }

  MutableMapEntry<K, V>& operator=(const MutableMapEntry<K, V>& other) = delete;

  MutableMapEntry<K, V>& operator=(MutableMapEntry<K, V>&& other) noexcept {
    _wrapped = std::move(other._wrapped);
    return *this;
  }

  K& Key() noexcept {
    return _wrapped.First();
  }

  const K& ConstKey() const noexcept {
    return _wrapped.ConstFirst();
  }

  V& Value() noexcept {
    return _wrapped.Second();
  }

  const V& ConstValue() const noexcept {
    return _wrapped.ConstSecond();
  }

  bool Equals(const MutableMapEntry<K, V>& other) const noexcept {
    return ConstKey() == other.ConstKey();
  }

  bool Equals(const K& other) const noexcept {
    return ConstKey() == other;
  }

  Ordering Compare(const MutableMapEntry<K, V>& other) const noexcept {
    return Ord<K>::Compare(ConstKey(), other.ConstKey());
  }

  Ordering Compare(const K& other) const noexcept {
    return Ord<K>::Compare(ConstKey(), other);
  }

  const MutableMapEntry<K, V>& Min(const MutableMapEntry<K, V>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const MutableMapEntry<K, V>& Max(const MutableMapEntry<K, V> other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }


  String Show() const noexcept {
    return Shows<K>::Show(ConstKey()) + String(": ") + Shows<V>::Show(ConstValue());
  }

};

}

#include <everest/mutable_containers/map/entry/eq.h>
#include <everest/mutable_containers/map/entry/ord.h>
#include <everest/mutable_containers/map/entry/show.h>
#include <everest/mutable_containers/map/entry/hashable.h>