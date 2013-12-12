#ifndef TRAITOROUS_TRAITS_MONAD
#define TRAITOROUS_TRAITS_MONAD 1

#include "applicative.h"

template<class S, class T>
class Monad : public Applicative<S, T> {
public:

  virtual S flat_map(std::function<S(T)> fn) = 0;

};

#endif
