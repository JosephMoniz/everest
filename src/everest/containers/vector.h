#pragma once

#include <stddef.h>
#include <cstdint>
#include <everest/types/int8.h>
#include "memory.h"

namespace everest {

enum class VectorLevel {
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN
};

template<class T>
class VectorLevelOne;

template<class T>
class VectorLevelTwo;

template<class T>
class VectorLevelThree;

template<class T>
class VectorLevelFour;

template<class T>
class VectorLevelFive;

template<class T>
class VectorLevelSix;

template<class T>
class VectorLevelSeven;

template<class T>
class VectorLevelOne final {

  size_t _length;

  T _items[32];

public:

  VectorLevelOne() noexcept : _length(0) { }

  VectorLevelOne(const T& item) noexcept : _length(1) {
    _items[0] = item;
  }

  VectorLevelOne(const VectorLevelOne& other, const T& item) noexcept {
    _length = other._length + 1;
    for (auto i = 0; i < other._length; i++) {
      _items[i] = other._items[i];
    }
    _items[other._length] = item;
  }

  VectorLevelOne(const T& item, const VectorLevelOne& other) noexcept {
    _length = other._length + 1;
    _items[0] = item;
    for (auto i = 0; i < other._length; i++) {
      _items[i + 1] = other._items[i];
    }
  }

};

template<class T>
class Vector final {

  VectorLevel _level;

  size_t _length;

  SharedMemory<int8_t> _memory;

public:

  

};

}