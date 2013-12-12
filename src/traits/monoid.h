#ifndef TRAITOROUS_TRAITS_MONOID
#define TRAITOROUS_TRAITS_MONOID 1

#include "add.h"
#include "zero.h"

template<class S>
class Monoid : public Add<S>, public Zero<S> { };

#endif
