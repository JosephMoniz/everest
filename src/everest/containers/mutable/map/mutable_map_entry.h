#pragma once

#include <utility>
#include <everest/containers/mutable/mutable_tuple.h>

namespace everest {

template<class K, class V>
class MutableMapEntry final {

  MutableTuple<K, V> _wrapped;

public:

  MutableMapEntry() : _wrapped() {}

  MutableMapEntry(K&& key, V&& value) noexcept : _wrapped(std::move(key), std::move(value)) { }

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

};

}

#include <everest/containers/mutable/map/entry/eq.h>
#include <everest/containers/mutable/map/entry/show.h>