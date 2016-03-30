#pragma once

#include <stddef.h>
#include <containers/option.h>

namespace traitorous {

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

  MutableMapEntry* Next() const noexcept {
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
      if (oldEntries[i] != nullptr) {
        auto old   = oldEntries[i];
        auto entry = old;
        while (entry != nullptr) {
          Put(entry->Key(), entry->Value());
          old   = entry;
          entry = entry->Next();
          delete old;
        }
      }
    }
    delete[] oldEntries;
  }

public:

  MutableMap() : MutableMap(128) { }

  MutableMap(size_t capacity) : _capacity(capacity), _size(0) {
    _entries = new MutableMapEntry<K, V>*[capacity];
    for (auto i = 0; i < capacity; i++) {
      _entries[i] = nullptr;
    }
  }

  ~MutableMap() {
    for (auto i = 0; i < _capacity; i++) {
      if (_entries[i] != nullptr) {
        MutableMapEntry* previous = nullptr;
        MutableMapEntry* entry    = _entries[i];
        while (entry != nullptr) {
          previous = entry;
          entry    = entry->Next();
          delete previous;
        }
      }
    }
    delete[] _entries;
  }

  Option<V&> Get(const K& key) const noexcept {
    auto hash = Hash(key) % _capacity;
    if (_entries[hash] != nullptr) {
      auto entry = _entries[hash];
      while(entry != nullptr && entry->Key() != key) {
        entry = entry->Next();
      }
      if (entry != nullptr) {
        return Some(entry->Value());
      } else {
        return None();
      }
    } else {
      return None();
    }
  }

  void Put(const K& key, const V& value) noexcept {
    auto hash = Hash(key) % _capacity;
    if (_entries[hash] == nullptr) {
      _entries[hash] = new MutableMapEntry(key, value);
      _size++;
    } else {
      auto entry = _entries[hash];
      while(entry->Next() != nullptr) {
        entry = entry->Next();
      }
      if (entry->Key() == key) {
        entry->SetValue(value);
      } else {
        entry->SetNext(new MutableMapEntry(key, value));
        _size++;
      }
    }
    if (_size == _capacity) {
      Resize();
    }
  }

  void Remove(const K& key) noexcept {
    auto hash = Hash(key) % _capacity;
    if (_entries[hash] != nullptr) {
      MutableMapEntry<K, V>* previous = nullptr;
      auto entry = _entries[hash];
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
