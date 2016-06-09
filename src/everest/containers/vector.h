#pragma once

#include <stddef.h>
#include <cstdint>
#include <everest/types/int8.h>
#include <everest/memory/memory.h>
#include <everest/containers/option.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/Pointable.h>
#include <everest/traits/unlawful/container.h>

namespace everest {
  
template<class T>
class Vector final {

  friend class Pointable<Vector<T>>;
  friend class Container<Vector<T>>;
  friend class Containable<Vector<T>, T>;
  friend class Droppable<Vector<T>>;
  friend class Eq<Vector<T>>;
  friend class Filterable<Vector<T>>;
  friend class Foldable<Vector<T>>;
  friend class Functor<Vector<T>>;
  friend class Hashable<Vector<T>>;
  friend class Monad<Vector<T>>;
  friend class Ord<Vector<T>>;
  friend class Queue<Vector<T>>;
  friend class Semigroup<Vector<T>>;
  friend class Stack<Vector<T>>;
  friend class Takeable<Vector<T>>;

  MutableVector<T> _wrapped;

public:

  Vector() noexcept : _wrapped() { }

  Vector(std::initializer_list<T> list) noexcept : _wrapped(list) { }

  Vector(const T* src, size_t length) noexcept {
    auto memory  = MutableMemory<T>(length);
    auto pointer = MutablePointer(memory);
    for (auto i = 0; i < length; i++) {
      src[i] = pointer[i];
    }
    _wrapped = MutableVector<T>(std::move(memory));
  }

  Vector(const Vector<T>& other) = delete;

  Vector(Vector<T>&& other) noexcept : _wrapped(std::move(other._wrapped)) {}

  // TODO: You should be able to construct an immutable vector from immutable memory
  /*
  Vector(Memory<T>&& memory) noexcept : _length(Length(memory)),
                                        _memory(std::move(memory)) { }
  */

  Vector(MutableVector<T>&& vector) noexcept : _wrapped(std::move(vector)) { }

  Option<const T&> At(size_t offset) const noexcept {
    if (offset < Length(_wrapped)) {
      return Some(Pointer(_wrapped)[offset]);
    } else {
      return None<const T&>();
    }
  }

};

}

#include "everest/containers/vector/pointable.h"
#include "everest/containers/vector/container.h"
#include "everest/containers/vector/containable.h"
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
