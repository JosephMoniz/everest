#pragma once

#include <stddef.h>
#include <cstdint>
#include <everest/types/int8.h>
#include <everest/memory/memory.h>
#include <everest/containers/option.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/droppable.h>
#include <everest/traits/unlawful/stack.h>
#include <everest/traits/unlawful/queue.h>

namespace everest {

template<class T>
class Vector final {

  size_t _length;

  Memory<T> _memory;

public:

  Vector() noexcept : _memory(Memory<T>()) { }

  Vector(std::initializer_list<T> list) noexcept {
    auto memory  = MutableMemory<T>(list.size());
    auto pointer = memory.MutablePointer();
    auto offset  = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
      pointer[offset++] = *it;
    }
    _length = list.size();
    _memory = memory;
  }

  Vector(const T* src, size_t length) noexcept {
    auto memory  = MutableMemory<T>(length);
    auto pointer = memory.MutablePointer();
    for (auto i = 0; i < length; i++) {
      src[i] = pointer[i];
    }
    _length = length;
    _memory = memory;
  }

  Vector(const Vector<T>& other) = delete;

  Vector(Vector<T>&& other) noexcept : _length(std::move(other._length)),
                                       _memory(std::move(other._memory)) {}
    

  Vector(Memory<T>&& memory) noexcept : _length(memory.Length()),
                                        _memory(std::move(memory)) { }

  Vector(MutableVector<T>&& vector) noexcept : _length(vector.Length()),
                                               _memory(std::move(vector._memory)) { }

  Vector(MutableVector<T>&& vector, size_t length) noexcept : _length(length),
                                                              _memory(std::move(vector._memory)) { }

  Vector(Vector<T>&& vector, size_t length) noexcept : _length(length),
                                                       _memory(std::move(vector._memory)) { }

  size_t Length() const noexcept {
    return _length;
  }

  const T* Pointer() const noexcept {
    return _memory.Pointer();
  }

  Option<const T&> At(size_t offset) const noexcept {
    if (offset < _length) {
      return Some(_memory.Pointer()[offset]);
    } else {
      return None<const T&>();
    }
  }

};

}

#include "everest/containers/vector/containable.h"
#include "everest/containers/vector/container.h"
#include "everest/containers/vector/droppable.h"
#include "everest/containers/vector/eq.h"
#include "everest/containers/vector/filterable.h"
#include "everest/containers/vector/foldable.h"
#include "everest/containers/vector/functor.h"
#include "everest/containers/vector/hashable.h"
#include "everest/containers/vector/hexable.h"
#include "everest/containers/vector/monad.h"
#include "everest/containers/vector/monoid.h"
#include "everest/containers/vector/ord.h"
#include "everest/containers/vector/queue.h"
#include "everest/containers/vector/semigroup.h"
#include "everest/containers/vector/show.h"
#include "everest/containers/vector/stack.h"
#include "everest/containers/vector/takeable.h"
#include "everest/containers/vector/zero.h"
