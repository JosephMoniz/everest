Traitorous
==========

Traitorous is an almost complete divorcement from C++'s standard template
library. The idea is to explore alternative methods for expressing
computation in C++ while sneaking in some additional composability through
the side door. Immutability and other general functional programming
practices have been important in the design process behind this library
and will continue to be the moral compass behind it.

Those familiar with Haskell's or Rust's type class hierarchy shouldn't be
to surprised by some of the `traits` present. The majority of them are
shamelessy stolen and just ported to C++ as abstract interfaces.

At the time of creation for this library `C++ concepts` (type classes)
have yet to be formaly standardized and implemented. Once they become
implemented in major compilers, it may be worth revisiting this
library leveraging `concepts` as the backbone instead.

Currently, this is still a heavy work in progress. Expect much to change.

Traits
------

Currently implemented traits are:

  * `Unwrappable<T>`
  * `Eq<T>`
  * `Ord<T>`
  * `Bounded<T>`
  * `Add<T>` (analogous to SemiGroup)
  * `Subtract<T>`
  * `Multiply<T>`
  * `Divide<T>`
  * `Remainder<T>`
  * `Zero<T>`
  * `One<T>`
  * `Monoid<T>` (An alias for Add<T> + Zero<T>)
  * `Show`

There are many notable traits missing such as Functor, Applicative and Monad.
These are on the radar but due to the nature of C++ will require me to come
up with a standard type erasure method and i don't want to jump to a solution
without doing more research. Expect them soon though.

Also, expect many other unlisted traits soon.

Types
-----

Currenty Implemented types are:

  * `Int`
  * `Int8`
  * `Int16`
  * `Int32`
  * `Int64`
  * `UInt`
  * `UInt8`
  * `UInt16`
  * `UInt32`
  * `UInt64`
  * `containers::monoid::Max<T>`
  * `containers::monoid::Min<T>`

Just basic numerics at the moment and some `Monoid<T>` containers. Many more
to come soon.
