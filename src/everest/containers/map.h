#pragma once

#include <stddef.h>
#include <everest/mutable_containers/mutable_map.h>
#include <everest/strings/string_joiner.h>

namespace everest {

template<class K, class V>
class Map final {

  MutableMap<K, V> _wrapped;

public:

  Map() : _wrapped() { }

  Map(MutableMap<K, V>&& map) noexcept : _wrapped(std::move(map)) { }

  bool Contains(const K& key) const noexcept {
    return _wrapped.Contains(key);
  }

  size_t Length() const noexcept {
    return _wrapped.Length();
  }

  bool IsEmpty() const noexcept {
    return _wrapped.IsEmpty();
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("Map(")
      .Add(StringJoiner(", ").Join(*this))
      .Add(")")
      .Build();
  }

  template <class F>
  void ForEach(F function) const noexcept {
    _wrapped.ForEach([&](MutableMapEntry<K, V>& entry) {
      function(entry);
    });
  }

  static Map<K, V> Zero() noexcept {
    return Map<K, V>();
  }

  class MapBuilder final {

    MutableMap<K, V> _map;

  public:

    MapBuilder() noexcept : _map() { }

    MapBuilder& Put(K&& key, V&& value) noexcept {
      _map.PutInPlace(std::move(key), std::move(value));
      return *this;
    }

    Map<K, V> Build() noexcept {
      return Map<K, V>(std::move(_map));
    };

  };

  static MapBuilder Builder() noexcept {
    return MapBuilder();
  };

};

}
