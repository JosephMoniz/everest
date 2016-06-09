#pragma once

#include <stddef.h>
#include <everest/containers/option.h>
#include <everest/containers/mutable/mutable_set.h>

namespace everest {

template<class K, class V>
class MutableMapEntry final {

  K _key;

  V _value;

public:

  MutableMapEntry() : _key(nullptr), _value(nullptr) {}

  MutableMapEntry(const K& key, const V& value) noexcept : _key(key),
                                                           _value(value) { }

  const K& Key() const noexcept {
    return _key;
  }

  void SetValue(const V& value) noexcept {
    _value = value;
  }

  const V& Value() const noexcept {
    return _value;
  }

};

template<class K, class V>
class MutableMap final {

  MutableSet<MutableMapEntry<K, V>> _set;

public:

  MutableMap() : _set() { }

  MutableMap(size_t capacity) : _set(capacity) { }

  Option<V&> Get(const K& key) const noexcept {
    //
  }

  void Put(const K& key, const V& value) noexcept {
    //
  }

  void Remove(const K& key) noexcept {
    //
  }

};

}
