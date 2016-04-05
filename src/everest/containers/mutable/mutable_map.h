#pragma once

#include <stddef.h>
#include <everest/containers/option.h>

namespace everest {

template<class K, class V>
class MutableMapEntry {

  K _key;

  V _value;

  MutableMapEntry* _next;

public:

  MutableMapEntry() : _key(nullptr), _value(nullptr), _next(nullptr) {}

  MutableMapEntry(const K& key, const V& value) noexcept : _key(key),
                                                           _value(value),
                                                           _next(nullptr) { }

  const K& Key() const noexcept {
    return _key;
  }

  void SetValue(const V& value) noexcept {
    _value = value;
  }

  const V& Value() const noexcept {
    return _value;
  }

  void SetNext(MutableMapEntry* next) noexcept {
    _next = next;
  }

  MutableMapEntry<K, V>* Next() const noexcept {
    return _next;
  }

};

template<class K, class V>
class MutableMap {

  MutableMapEntry<K, V>** _entries;

  size_t _capacity;

  size_t _size;

  void Resize() noexcept {
    auto previousCapacity = _capacity;
    auto oldEntries       = _entries;
    _capacity             *= 2;
    _entries              = new MutableMapEntry<K, V>*[_capacity];
    for (auto i = 0; i < _capacity; i++) {
      _entries[i] = 0;
    }
    for (auto i = 0; i < previousCapacity; i++) {
      for (auto entry = oldEntries[i]; entry != nullptr; entry = entry->Next()) {
        Put(entry->Key(), entry->Value());
      }
    }
    FreeMapEntries(oldEntries, previousCapacity);
  }

  void FreeMapEntries(MutableMapEntry<K, V>** entries, size_t capacity) noexcept {
    for (auto i = 0; i < capacity; i++) {
      if (entries[i] != nullptr) {
        MutableMapEntry* previous = nullptr;
        MutableMapEntry* entry    = entries[i];
        while (entry != nullptr) {
          previous = entry;
          entry    = entry->Next();
          delete previous;
        }
      }
    }
    delete[] entries;
  }

  MutableMapEntry<K, V>** FindBucket(const K& key) const noexcept {
    return FindBucketFromHash(Hash(key));
  };

  MutableMapEntry<K, V>** FindBucketFromHash(int hash) const noexcept {
    return &_entries[hash % _capacity];
  };

  MutableMapEntry<K, V>* FindNearestEntryInBucket(MutableMapEntry<K, V>* entry, const K& key) const noexcept {
    while(entry->Next() != nullptr && entry->Value() != key) {
      entry = entry->Next();
    }
    return entry;
  };

public:

  MutableMap() : MutableMap(128) { }

  MutableMap(size_t capacity) : _capacity(capacity), _size(0) {
    _entries = new MutableMapEntry<K, V>*[capacity];
    for (auto i = 0; i < capacity; i++) {
      _entries[i] = nullptr;
    }
  }

  ~MutableMap() {
    FreeMapEntries(_entries, _capacity);
  }

  Option<V&> Get(const K& key) const noexcept {
    auto bucket = FindBucket(key);
    auto entry  = *bucket;
    if (entry != nullptr) {
      auto closest = FindNearestEntryInBucket(entry, key);
      if (closest->Key() != key) {
        return Some(entry->Value());
      } else {
        return None();
      }
    } else {
      return None();
    }
  }

  void Put(const K& key, const V& value) noexcept {
    auto hash   = Hash(key) % _capacity;
    auto bucket = FindBucket(hash);
    auto entry  = *bucket;
    if (entry == nullptr) {
      _entries[hash] = new MutableMapEntry(key, value);
      _size++;
    } else {
      auto closest = FindNearestEntryInBucket(entry, key);
      if (closest->Key() == key) {
        closest->SetValue(value);
      } else {
        closest->SetNext(new MutableMapEntry(key, value));
        _size++;
      }
    }
    if (_size == _capacity) {
      Resize();
    }
  }

  void Remove(const K& key) noexcept {
    auto hash   = Hash(key) % _capacity;
    auto bucket = FindBucketFromHash(key);
    auto entry  = *bucket;
    if (entry != nullptr) {
      MutableMapEntry<K, V>* previous = nullptr;
      while(entry != nullptr && entry->Key() != key) {
        previous = entry;
        entry    = entry->Next();
      }
      if (entry != nullptr && entry->Key() == key) {
        if (previous == nullptr) {
          auto next = entry->Next();
          delete entry;
          _entries[hash] = next;
        } else {
          auto next = entry->Next();
          delete entry;
          previous->SetNext(next);
        }
        _size--;
      }
    }
  }

};

}
