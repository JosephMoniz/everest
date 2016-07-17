Everest
=======
[![Build Status](https://travis-ci.org/JosephMoniz/everest.svg?branch=master)](https://travis-ci.org/JosephMoniz/everest)

Everest is an almost complete divorcement from C++'s standard template
library. The idea is to explore alternative methods for expressing
computation in C++ while sneaking in some additional composability through
the side door. Immutability and other general functional programming
practices have been important in the design process behind this library
and will continue to be the moral compass behind it. That being said
this library is not strictly FP and abides by Clojure's transient principal.

Those familiar with Haskell's or Rust's type class hierarchy shouldn't be
to surprised by some of the `traits` present. The majority of them are
shamelessly stolen and just ported to C++ via template specialization.

At the time of creation for this library `C++ concepts` (type classes)
have yet to be formally standardized and implemented. Once they become
implemented in major compilers, it may be worth revisiting this
library leveraging `concepts` as the backbone instead.

Currently, this is still a heavy work in progress. Expect much to change.

Memory Management
-----------------

  + [`Memory<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/memory/mutable_memory.h)
  + [`MutableMemory<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/memory/mutable_memory.h)
  + [`GrowableMemory<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/memory/growable_memory.h)
  + [`Shared<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/memory/shared.h)
  + [`Unique<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/memory/unique.h)
  
Function Types
--------------

  + [`Function<T, R>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/functions/types.h)
  + [`BiFunction<T, U, R>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/functions/types.h)
  + [`Predicate<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/functions/types.h)
  + [`Supplier<R>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/functions/types.h)
  + [`Consumer<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/functions/types.h)
  + [`Thunk`](https://github.com/JosephMoniz/everest/blob/master/src/everest/functions/types.h)
  
Containers
----------

### Immutable Containers

  + [`Array<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/array.h)
  + [`Checked<E, S>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/checked.h)
  + [`Option<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/option.h)
  + [`Map<K, V>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/map.h)
  + [`Vector<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/vector.h)
  + [`Set<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/set.h)

### Mutable Containers

  + [`MutableArray<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/mutable/mutable_array.h)
  + [`MutableVector<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/mutable/mutable_vector.h)
  + [`MutableMap<K, V>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/mutable/mutable_map.h)
  + [`MutableSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/mutable/mutable_set.h)

### Immutable CRDTs

  + [`GCounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/crdt/counters/gcounter.h)
  + [`GACounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/crdt/counters/gacounter.h)
  + [`PNCounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/crdt/counters/pncounter.h)
  + [`PNACounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/crdt/counters/pnacounter.h)
  
### Immutable Monoids

  + [`MaxMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/max_monoid.h)
  + [`MinMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/min_monoid.h)
  + [`AverageMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/average_monoid.h)
  + [`StdDeviationMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/std_deviation_monoid.h)

Concurrency
-----------

### FRP Concurrency Primitives

  + [`Box<E, S>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/concurrency/box.h)
  + [`Conveyor<E, S>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/concurrency/conveyor.h)

Traits
------

### Lawful Traits

  + [`Semigroup<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/lawful/semigroup.h)
  + [`Monoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/lawful/monoid.h)
  + [`Functor<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/lawful/functor.h)
  + [`Alternative<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/lawful/alternative.h)
  + [`Monad<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/lawful/monad.h)
  + [`Foldable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/lawful/foldable.h)
  + [`MonadPlus<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/lawful/monad_plus.h)

### Unlawful Traits

  + [`BitAnd<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/bit_and.h)
  + [`BitOr<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/bit_or.h)
  + [`BitXor<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/bit_xor.h)
  + [`Bounded<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/bounded.h)
  + [`Containable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/containable.h)
  + [`Container<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/container.h)
  + [`Disjoinable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/disjoinable.h)
  + [`Divide<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/divide.h)
  + [`Droppable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/droppable.h)
  + [`Enumerable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/enumerable.h)
  + [`Enumerator<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/enumerator.h)
  + [`Eq<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/eq.h)
  + [`Filterable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/filterable.h)
  + [`Hashable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/hashable.h)
  + [`Hexable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/hexable.h)
  + [`Intersectable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/intersectable.h)
  + [`Multiply<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/multiply.h)
  + [`Negate<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/negate.h)
  + [`One<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/one.h)
  + [`Ord<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/ord.h)
  + [`Queue<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/queue.h)
  + [`Remainder<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/remainder.h)
  + [`ShiftLeft<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/shift_left.h)
  + [`ShiftRight<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/shift_right.h)
  + [`Show<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/show.h)
  + [`Stack<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/stack.h)
  + [`Subtract<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/subtract.h)
  + [`Takeable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/takeable.h)
  + [`Unwrappable<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/unwrappable.h)
  + [`Zero<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/traits/unlawful/zero.h)
  
Todo
----
  + A free list based `Pool<T>` container
  + Implement thread pools
  + Implement `ConcurrentShared<T>`
  + An IO Abstraction suite around `kqueue()`
  + An thread based facade to `mlock`/`munlock` for async `mmap`