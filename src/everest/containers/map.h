#pragma once

#include <stddef.h>
#include <everest/mutable_containers/mutable_map.h>

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
    return Take(out.Length() - 2, std::move(out)) + String(")");
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

}
