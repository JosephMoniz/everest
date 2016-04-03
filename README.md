Everest
=======
[![Build Status](https://travis-ci.org/JosephMoniz/everest.svg?branch=master)](https://travis-ci.org/JosephMoniz/everest)

Everest is an almost complete divorcement from C++'s standard template
library. The idea is to explore alternative methods for expressing
computation in C++ while sneaking in some additional composability through
the side door. Immutability and other general functional programming
practices have been important in the design process behind this library
and will continue to be the moral compass behind it. That being said
this library is not strictly FP and abides by clojures transient principal.

Those familiar with Haskell's or Rust's type class hierarchy shouldn't be
to surprised by some of the `traits` present. The majority of them are
shamelessy stolen and just ported to C++ via template specialization.

At the time of creation for this library `C++ concepts` (type classes)
have yet to be formaly standardized and implemented. Once they become
implemented in major compilers, it may be worth revisiting this
library leveraging `concepts` as the backbone instead.

Currently, this is still a heavy work in progress. Expect much to change.

Todo
----

  + Make String into a Rope implementation
  + Implement `Vector<T>` as an immutable 32 way HAMT
  + Implement `Map<K, V>` as an immutable 32 way HAMT
  + A free list based `Pool<T>` container
  + RAII Concurrency utils such as `Mutex`
  + Implement thread pools
  + Implement `ConcurrentShared<T>`
  + An IO Abstraction suite around `kqueue()`
  + An thread based facade to `mlock`/`munlock` for async `mmap`
  + Trait for converting things to hex strings
  + Crypto primitives (md5/sha1)
