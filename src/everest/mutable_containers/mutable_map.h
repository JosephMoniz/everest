#pragma once

#include <stddef.h>
#include <everest/mutable_containers/map/mutable_map_entry.h>
#include <everest/mutable_containers/mutable_set.h>

namespace everest {

template<class K, class V>
class MutableMap final {

  MutableSet<MutableMapEntry<K, V>> _set;

public:

  MutableMap() noexcept : _set() { }

  MutableMap(MutableSet<MutableMapEntry<K, V>>&& set) noexcept : _set(std::move(set)) { }

  MutableMap<K, V> Copy() const noexcept {
    return MutableMap(_set.Copy());
  }

  size_t Length() const noexcept {
    return _set.Length();
  }

  bool IsEmpty() const noexcept {
    return _set.IsEmpty();
  }

  MutableMap<K, V> Put(K&& key, V&& value) const noexcept {
    auto copy = Copy();
    return copy.PutInPlace(std::move(key), std::move(value));
  }

  MutableMap<K, V> Put(MutableMap<K, V>&& source) const noexcept {
    auto copy = Copy();
    ForEach(source, [&](MutableMapEntry<K, V>& entry) {
      copy.PutInPlace(std::move(entry.Key()), std::move(entry.Value()));
    });
    return copy;
  }

  Option<const V*> Get(const K& key) const noexcept {
    return _set
      .Find(key)
      .Map([](const MutableMapEntry<K, V>* entry) { return &entry->ConstValue(); });
  };

  bool Contains(const K& key) const noexcept {
    return _set.Find(key).IsSome();
  }

  bool Equals(const MutableMap<K, V>& other) const noexcept {
    return _set.Equals(other._set);
  }

  template <class F>
  void ForEach(F function) const noexcept {
    _set.ForEach(function);
  }

  MutableMap<K, V>& PutInPlace(K&& key, V&& value) noexcept {
    _set.AddInPlace(MutableMapEntry<K, V>(std::move(key), std::move(value)));
    return *this;
  }

  MutableMap<K, V>& PutInPlace(MutableMap<K, V>&& source) noexcept {
    ForEach(source, [&](MutableMapEntry<K, V>& entry) {
      PutInPlace(std::move(entry.Key()), std::move(entry.Value()));
    });
  }

  Option<V*> GetInPlace(const K& key) noexcept {
    return _set
      .FindInPlace(key)
      .Map([](MutableMapEntry<K, V>* entry) { return &entry->Value(); });
  };

  MutableMap<K, V>& RemoveInPlace(const K& key) noexcept {
    _set.RemoveSimilarInPlace(key);
    return *this;
  }

  MutableMap<K, V>& RemoveInPlace(const MutableMap<K, V>& source) noexcept {
    source.ForEach([&](MutableMapEntry<K, V>& entry) {
      RemoveInPlace(entry.Key());
    });
    return *this;
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  MutableMap<K, V>& RemoveInPlace(const U& source) noexcept {
    source.ForEach([&](const K& item) {
      RemoveInPlace(item);
    });
    return *this;
  }

  MutableMap<K, V> Add(const MutableMap<K, V>& other) const noexcept {
    auto result = MutableMap<K, V>();
    ForEach([&](const MutableMapEntry<K, V>& entry) {
      result.PutInPlace(Copyable<K>::Copy(entry.ConstKey()), Copyable<V>::Copy(entry.ConstValue()));
    });
    other.ForEach([&](const MutableMapEntry<K, V>& entry) {
      result.Get(entry.ConstKey()).Match(
        [&]() {
          result.PutInPlace(Copyable<K>::Copy(entry.ConstKey()), Copyable<V>::Copy(entry.ConstValue()));
        },
        [&](const V* value) {
          result.PutInPlace(Copyable<K>::Copy(entry.ConstKey()), *value + entry.ConstValue());
        }
      );
    });
    return result;
  }

  // TODO: Make test
  // TODO: Make trait
  MutableMap<K, V>& AddInPlace(const MutableMap<K, V>& other) noexcept {
    other.ForEach([&](const MutableMapEntry<K, V>& entry) {
      GetInPlace(entry.ConstKey()).Match(
        [&]() {
          PutInPlace(Copyable<K>::Copy(entry.ConstKey()), Copyable<V>::Copy(entry.ConstValue()));
        },
        [&](V* value) {
          *value = *value + entry.ConstValue();
        }
      );
    });
    return *this;
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutableMap(")
      .Add(StringJoiner(", ").Join<MutableMap<K, V>, MutableMapEntry<K, V>>(*this))
      .Add(")")
      .Build();
  }

  static MutableMap<K, V> Zero() noexcept {
    return MutableMap<K, V>();
  }

  class MutableMapBuilder final {

    MutableMap<K, V> _map;

  public:

    MutableMapBuilder() noexcept : _map() { }

    MutableMapBuilder& Put(K&& key, V&& value) noexcept {
      _map.PutInPlace(std::move(key), std::move(value));
      return *this;
    }

    MutableMap<K, V> Build() noexcept {
      return MutableMap<K, V>(std::move(_map));
    };

  };

  static MutableMapBuilder Builder() noexcept {
    return MutableMapBuilder();
  };

};

}