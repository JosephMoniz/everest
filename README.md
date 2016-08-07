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

  + [`MutableArray<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/mutable_containers/mutable_array.h)
  + [`MutableVector<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/mutable_containers/mutable_vector.h)
  + [`MutableMap<K, V>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/mutable_containers/mutable_map.h)
  + [`MutableSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/mutable_containers/mutable_set.h)
  + [`MutableSortedVectorMap<K, V>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/mutable_containers/mutable_sorted_vector_map.h)
  + [`MutableSortedVectorSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/mutable_containers/mutable_sorted_vector_set.h)  
  + [`MutableBitSet`](https://github.com/JosephMoniz/everest/blob/master/src/everest/mutable_containers/mutable_bit_set.h)

### Immutable CRDTs

  + [`GCounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/counters/gcounter.h)
  + [`GACounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/counters/gacounter.h)
  + [`PNCounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/counters/pncounter.h)
  + [`PNACounter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/counters/pnacounter.h)
  + [`GSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/sets/gset.h)
  + [`LWWSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/sets/lwwset.h)
  + [`MCSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/sets/mcset.h)
  + [`ORSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/sets/orset.h)
  + [`TPSet<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crdt/sets/tpset.h)
  
### Probablistic Containers

  + [`BloomFilter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/probablistic/bloom_filter.h)
  + [`MutableBloomFilter<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/probablistic/mutable/mutable_bloom_filter.h)
  
### Immutable Monoids

  + [`MaxMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/max_monoid.h)
  + [`MinMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/min_monoid.h)
  + [`AverageMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/average_monoid.h)
  + [`StdDeviationMonoid<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/containers/monoids/std_deviation_monoid.h)
  
### Deciders

  + [`BinaryDecider<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/deciders/binary_decider.h)
  + [`MultiVariantDecider<T>`](https://github.com/JosephMoniz/everest/blob/master/src/everest/deciders/multi_variant_decider.h)
  
Cryptography
------------

### Hash Methods
  + [`Md5`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/md5.h)
  + [`Sha1`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha1.h)
  + [`Sha224`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha224.h)
  + [`Sha256`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha256.h)
  + [`Sha384`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha384.h)
  + [`Sha512`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha512.h)
  
### Hash Sinks
  + [`Md5Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/md5/md5_sink.h)
  + [`Sha1Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha1/sha1_sink.h)
  + [`Sha224Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha224/sha224_sink.h)
  + [`Sha256Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha256/sha256_sink.h)
  + [`Sha384Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha384/sha384_sink.h)
  + [`Sha512Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hash/sha512/sha512_sink.h)

### HMAC Methods
  + [`Md5`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/md5.h)
  + [`Sha1`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha1.h)
  + [`Sha224`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha224.h)
  + [`Sha256`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha256.h)
  + [`Sha384`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha384.h)
  + [`Sha512`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha512.h)
  
### HMAC Sinks
  + [`Md5Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/md5/md5_sink.h)
  + [`Sha1Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha1/sha1_sink.h)
  + [`Sha224Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha224/sha224_sink.h)
  + [`Sha256Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha256/sha256_sink.h)
  + [`Sha384Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha384/sha384_sink.h)
  + [`Sha512Sink`](https://github.com/JosephMoniz/everest/blob/master/src/everest/crypto/hmac/sha512/sha512_sink.h)

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
   