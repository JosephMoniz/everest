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
      .Map([](MutableMapEntry<K, V>& entry) { return &entry.Value(); });
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
    ForEach([&](MutableMapEntry<K, V>& entry) {
      result.PutInPlace(Copyable<K>::Copy(entry.Key()), Copyable<V>::Copy(entry.Value()));
    });
    other.ForEach([&](MutableMapEntry<K, V>& entry) {
      result.Get(entry.Key()).Match(
        [&]() {
          result.PutInPlace(Copyable<K>::Copy(entry.Key()), Copyable<V>::Copy(entry.Value()));
        },
        [&](const V* value) {
          result.PutInPlace(Copyable<K>::Copy(entry.Key()), *value + entry.Value());
        }
      );
    });
    return result;
  }

  String Show() const noexcept {
    auto out = String("MutableMap(");
    ForEach([&](const MutableMapEntry<K, V>& entry) {
      out = std::move(out) + entry.Show() + String(", ");
    });
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

  static MutableMap<K, V> Zero() noexcept {
    return MutableMap<K, V>();
  }

};

}