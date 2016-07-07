#pragma once

#include <stddef.h>
#include <everest/containers/mutable/mutable_map.h>

namespace everest {

template<class K, class V>
class Map final {

  friend class Containable<Map<K, V>>;
  friend class Container<Map<K, V>>;
  friend class Shows<Map<K, V>>;

  MutableMap<K, V> _wrapped;

public:

  Map() : _wrapped() { }

};

template<class K, class V>
class Containable<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const K& key, const Map<K, V>& map) noexcept {
    return Containable<MutableMap<K, V>>::Contains(key, map._wrapped);
  }

};

template <class K, class V>
class Container<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Map<K, V>& map) noexcept {
    return Container<MutableMap<K, V>>::Length(map._wrapped);
  }

  static constexpr bool IsEmpty(const Map<K, V>& map) noexcept {
    return Container<MutableMap<K, V>>::IsEmpty(map._wrapped);
  }

};

template <class K, class V>
class Shows<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static const String Show(const Map<K, V>& map) noexcept {
    auto out = String("Map(");
    ForEach(map._wrapped, [&](const MutableMapEntry<K, V>& entry) {
      out = out + Shows<MutableMapEntry<K, V>>::Show(entry) + String(", ");
    });
    return Take(Length(out) - 2, std::move(out)) + String(")");
  }

};

template <class K, class V>
class MapEntry<K, V> final {

  const K& _key;

  const V& _value;

public:

  MapEntry(const K& key, const V& value) noexcept : _key(key),
                                                    _value(value) { }

  const K& Key() const noexcept {
    return _key;
  }

  const V& Value() const noexcept {
    return _value;
  }

};

template <class K, class V>
class Iteration<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Map<K, V>& container, const F& function) noexcept {
    ForEach(container, [&](MutableMapEntry<K, V>& entry) {
      function(MapEntry<K, V>(entry.Key(), entry.Value()));
    });
  }

};

template<class K, class V>
class ZeroVal<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static Map<K, V> Zero() noexcept {
    return Map<K, V>();
  }

};

}
