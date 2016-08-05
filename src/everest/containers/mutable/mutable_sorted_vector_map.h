#pragma once

#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/containers/mutable/mutable_sorted_vector_set.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap final {

  MutableSortedVectorSet<MutableMapEntry<K, V>> _set;

public:

  MutableSortedVectorMap() noexcept : _set() { }

  MutableSortedVectorMap(MutableSortedVectorSet<MutableMapEntry<K, V>>&& set) noexcept : _set(std::move(set)) { }

  MutableSortedVectorMap<K, V> Copy() const noexcept {
    return MutableSortedVectorMap(_set.Copy());
  }

  size_t Length() const noexcept {
    return _set.Length();
  }

  bool IsEmpty() const noexcept {
    return _set.IsEmpty();
  }

  MutableSortedVectorMap<K, V> Put(K&& key, V&& value) const noexcept {
    auto copy = Copy();
    return copy.PutInPlace(std::move(key), std::move(value));
  }

  MutableSortedVectorMap<K, V> Put(MutableSortedVectorMap<K, V>&& source) const noexcept {
    auto copy = Copy();
    source.ForEach([&](MutableMapEntry<K, V>& entry) {
      copy.PutInPlace(std::move(entry.Key()), std::move(entry.Value()));
    });
    return copy;
  }

  const V* Get(const K& key) const noexcept {
    auto pointer = _set.Find(key);
    return pointer != nullptr
      ? &pointer->ConstValue()
      : nullptr;
  };

  bool Contains(const K& key) const noexcept {
    return _set.Find(key) != nullptr;
  }

  bool Equals(const MutableSortedVectorMap<K, V>& other) const noexcept {
    return _set.Equals(other._set);
  }

  template <class F>
  void ForEach(F function) const noexcept {
    _set.ForEach(function);
  }

  MutableSortedVectorMap<K, V>& PutInPlace(K&& key, V&& value) noexcept {
    _set.AddInPlace(MutableMapEntry<K, V>(std::move(key), std::move(value)));
    return *this;
  }

  MutableSortedVectorMap<K, V>& PutInPlace(MutableSortedVectorMap<K, V>&& source) noexcept {
    source.ForEach([&](MutableMapEntry<K, V>& entry) {
      PutInPlace(std::move(entry.Key()), std::move(entry.Value()));
    });
  }

  V* GetInPlace(const K& key) noexcept {
    auto pointer = _set.FindInPlace(key);
    return pointer != nullptr
      ? &pointer->Value()
      : nullptr;
  };

  MutableSortedVectorMap<K, V>& RemoveInPlace(const K& key) noexcept {
    _set.RemoveSimilarInPlace(key);
    return *this;
  }

  MutableSortedVectorMap<K, V>& RemoveInPlace(const MutableSortedVectorMap<K, V>& source) noexcept {
    source.ForEach([&](MutableMapEntry<K, V>& entry) {
      RemoveInPlace(entry.Key());
    });
    return *this;
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  MutableSortedVectorMap<K, V>& RemoveInPlace(const U& source) noexcept {
    source.ForEach([&](const K& item) {
      RemoveInPlace(item);
    });
    return *this;
  }

  MutableSortedVectorMap<K, V> Add(const MutableSortedVectorMap<K, V>& other) const noexcept {
    return MutableSortedVectorMap(_set.Add(other._set));
  }

  String Show() const noexcept {
    auto out = String("MutableMap(");
    ForEach([&](const MutableMapEntry<K, V>& entry) {
      out = std::move(out) + entry.Show() + String(", ");
    });
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

  static MutableSortedVectorMap<K, V> Zero() noexcept {
    return MutableSortedVectorMap<K, V>();
  }

};

}