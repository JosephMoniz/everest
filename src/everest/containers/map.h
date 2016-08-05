#pragma once

#include <stddef.h>
#include <everest/containers/mutable/mutable_map.h>

namespace everest {

template<class K, class V>
class Map final {

  MutableMap<K, V> _wrapped;

public:

  Map() : _wrapped() { }

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
    auto out = String("Map(");
    _wrapped.ForEach([&](const MutableMapEntry<K, V>& entry) {
      out = out + Shows<MutableMapEntry<K, V>>::Show(entry) + String(", ");
    });
    return Take(Length(out) - 2, std::move(out)) + String(")");
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

};

template<class K, class V>
class Containable<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const K& key, const Map<K, V>& map) noexcept {
    return map.Contains(key);
  }

};

template <class K, class V>
class Container<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Map<K, V>& map) noexcept {
    return map.Length();
  }

  static bool IsEmpty(const Map<K, V>& map) noexcept {
    return map.IsEmpty();
  }

};

template <class K, class V>
class Shows<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Map<K, V>& map) noexcept {
    return map.Show();
  }

};

template <class K, class V>
class Iteration<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Map<K, V>& container, F function) noexcept {
    container.ForEach(function);
  }

};

template<class K, class V>
class ZeroVal<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static Map<K, V> Zero() noexcept {
    return Map<K, V>::Zero();
  }

};

}
