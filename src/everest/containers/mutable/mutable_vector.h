#pragma once

#include <stddef.h>
#include <everest/containers/option.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/anyable.h>
#include <everest/traits/unlawful/mutable/mutable_filter.h>
#include <everest/traits/unlawful/mutable/mutable_stack.h>
#include <everest/traits/unlawful/mutable/mutable_drop.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

#include <everest/traits/unlawful/iteration.h>
#include <everest/traits/unlawful/copyable.h>


namespace everest {

template<class T>
class Vector;

template<class T>
class MutableVector final {

  friend class Vector<T>;
  friend class Container<MutableVector<T>>;
  friend class Pointable<MutableVector<T>>;
  friend class MutableFilter<MutableVector<T>>;
  friend class MutableStack<MutableVector<T>>;
  friend class MutableDrop<MutableVector<T>>;
  friend class Iteration<MutableVector<T>>;
  friend class MutableFind<MutableVector<T>>;

  size_t _length;

  MutableMemory<T> _memory;

public:

  MutableVector() noexcept : _length(0), _memory() { }

  MutableVector(size_t capacity) noexcept : _length(0),
                                            _memory(MutableMemory<T>(capacity)){ }

  MutableVector(std::initializer_list<T> list) noexcept : _length(list.size()),
                                                          _memory(list.size())
  {
    auto pointer = MutablePointer(_memory);
    auto offset  = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
      pointer[offset++] = *it;
    }
  }

  MutableVector(MutableMemory<T>&& memory) noexcept : _length(Length(memory)),
                                                      _memory(std::move(memory)) { }

  MutableVector(const MutableVector<T>& other) = delete;

  MutableVector(MutableVector<T>&& other) noexcept : _length(other._length),
                                                     _memory(std::move(other._memory))
  {
    other._length = 0;
  }

  MutableVector<T>& operator=(const MutableVector<T>& other) = delete;

  MutableVector<T>& operator=(MutableVector<T>&& other) noexcept {
    _memory       = std::move(other._memory);
    _length       = other._length;
    return *this;
  }

  void Reserve(size_t size) noexcept {
    if (_memory == nullptr) {
      _memory = MutableMemory<T>((size == 0) ? 32 : size);
    } else {
      if (size > Length(_memory)) {
        auto self = this;
        auto old  = std::move(_memory);
        _memory   = MutableMemory<T>(size);
        ForEach(old, [&](T&& item) {
          PushInPlace(std::move(item), *self);
        });
      }
    }
  }

  Option<T&> At(size_t offset) const noexcept {
    if (offset < _length && offset > 0 && _memory != nullptr) {
      return Some(Pointer(_memory)[offset]);
    } else {
      return None<T&>();
    }
  }

};

}

#include <everest/containers/mutable/vector/anyable.h>
#include <everest/containers/mutable/vector/containable.h>
#include <everest/containers/mutable/vector/container.h>
#include <everest/containers/mutable/vector/copyable.h>
#include <everest/containers/mutable/vector/droppable.h>
#include <everest/containers/mutable/vector/eq.h>
#include <everest/containers/mutable/vector/filterable.h>
#include <everest/containers/mutable/vector/foldable.h>
#include <everest/containers/mutable/vector/functor.h>
#include <everest/containers/mutable/vector/hashable.h>
#include <everest/containers/mutable/vector/hexable.h>
#include <everest/containers/mutable/vector/iteration.h>
#include <everest/containers/mutable/vector/monad.h>
#include <everest/containers/mutable/vector/monoid.h>
#include <everest/containers/mutable/vector/mutable_add.h>
#include <everest/containers/mutable/vector/mutable_drop.h>
#include <everest/containers/mutable/vector/mutable_filter.h>
#include <everest/containers/mutable/vector/mutable_find.h>
#include <everest/containers/mutable/vector/mutable_stack.h>
#include <everest/containers/mutable/vector/ord.h>
#include <everest/containers/mutable/vector/pointable.h>
#include <everest/containers/mutable/vector/queue.h>
#include <everest/containers/mutable/vector/semigroup.h>
#include <everest/containers/mutable/vector/shows.h>
#include <everest/containers/mutable/vector/stack.h>
#include <everest/containers/mutable/vector/takeable.h>
#include <everest/containers/mutable/vector/zero.h>
