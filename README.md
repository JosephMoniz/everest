Everest
=======
[![Build Status](https://travis-ci.org/JosephMoniz/everest.svg?branch=master)](https://travis-ci.org/JosephMoniz/everest)

A modern C++ framework that focuses on simplicity and correctness.

TODO
----

  + [ ] Disable copy constructors for primitive containers
  + [ ] Language Experiments
    + [ ] Can we use Concepts in our compilers yet?
    + [ ] Can we use Modules in our compilers yet?
    + [ ] Can we use Variant yet?
  + [x] IO
    + [x] TCP Client
      + [x] Verify it's empirically working
      + [x] Add remote address storage
      + [x] Tests
    + [x] TCP Server Listener
      + [x] Implement
      + [x] Add remote address storage
      + [x] Verify it's empirically working
      + [x] Test
  + [ ] Testing Changes
    + [ ] Collect test failures as we execute and report at end of test runs
  + [ ] Concurrency
    + [ ] Channels
    + [ ] Thread pools
      + [x] SingleWorkerPool
      + [x] FixedWorkerPool
      + [ ] CachedThreadPool
  + [ ] Data Structures
    + [x] Circular Buffer
    + [ ] Unrolled Linked List
    + [ ] Implement Cache Data Structures
      + [ ] FixedCountLRUCache
      + [ ] FixedSizeLRUCache
    + [x] Mutable Sets
      + [x] MutableSortedVectorSet
        + [x] Add set intersection operation
        + [x] Add set difference operation
      + [x] MutableSet
        + [x] Add set intersection operation
        + [x] Add set difference operation
     + [x] Sets
       + [x] SortedVectorSet
         + [x] Add set intersection operation
         + [x] Add set difference operation
       + [x] Set
         + [x] Add set intersection operation
         + [x] Add set difference operation
  + [x] Deciders
  + [x] Feature Flags
    + [x] Binary Feature Flags
      + [x] Definition DSL
      + [x] Override DSL
    + [x] Multi-Variant Feature Flags
      + [x] Definition DSL
      + [x] Override DSL
   