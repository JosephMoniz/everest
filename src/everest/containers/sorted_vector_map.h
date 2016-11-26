#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_map.h>
#include <everest/strings/string_joiner.h>

namespace everest {

template <class K, class V>
class SortedVectorMap final {

  MutableSortedVectorMap<K, V> _map;

public:

  SortedVectorMap() noexcept : _map() { }

  SortedVectorMap(MutableSortedVectorMap&& map) noexcept : _map(std::move(map)) { }

  SortedVectorMap<K, V> Copy() const noexcept {
    return SortedVectorMap(_map.Copy());
  }

  size_t Length() const noexcept {
    return _map.Length();
  }

  bool IsEmpty() const noexcept {
    return _map.IsEmpty();
  }

  SortedVectorMap<K, V> Put(K&& key, V&& value) const noexcept {
    return SortedVectorMap<K, V>(_map.Put(std::move(key), std::move(value)));
  }

  SortedVectorMap<K, V> Put(SortedVectorMap<K, V>&& source) const noexcept {
    return SortedVectorMap<K, V>(std::move(source));
  }

  const V* Get(const K& key) const noexcept {
    return _map.Get(key);
  };

  // TODO: Make trait
  // TODO: Make test
  Option<const V*> GetCeil(const K& key) const noexcept {
    return _map.GetCeil(key);
  };

  // TODO: Make trait
  // TODO: Make test
  Option<const V*> GetFloor(const K& key) const noexcept {
    return _map.GetFloor(key);
  };

  // TODO: Make trait
  // TODO: Make test
  Option<const V*> FirstValue() const noexcept {
    return _map.FirstValue();
  };

  // TODO: Make trait
  // TODO: Make test
  Option<const V*> LastValue() const noexcept {
    return _map.LastValue();
  };

  bool Contains(const K& key) const noexcept {
    return _map.Contains(key);
  }

  bool Equals(const SortedVectorMap<K, V>& other) const noexcept {
    return _map.Equals(other._map);
  }

  template <class F>
  void ForEach(F function) const noexcept {
    _map.ForEach(function);
  }

  SortedVectorMap<K, V> Add(const SortedVectorMap<K, V>& other) const noexcept {
    return SortedVectorMap(_map.Add(other._map));
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("SortedVectorMap(")
      .Add(StringJoiner(", ").Join(*this))
      .Add(")")
      .Build();
  }

  static SortedVectorMap<K, V> Zero() noexcept {
    return SortedVectorMap<K, V>();
  }

};

}