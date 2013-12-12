#ifndef TRAITOROUS_TRAITS_APPLICATIVE
#define TRAITOROUS_TRAITS_APPLICATIVE 1

#include "functor.h"

template<class S, class A>
class Applicative : public Functor<S, T> {
public:

  virtual S ap(S next) = 0;

};

#endif
