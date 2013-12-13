#ifndef TRAITOROUS_TRAITS_FUNCTOR
#define TRAITOROUS_TRAITS_FUNCTOR 1

#include <memory>

#include "types/any.h"

template<template<class> class S, class T>
class Functor {
public:

  virtual std::shared_ptr<S<Any>>
  map(std::function<std::shared_ptr<Any>(std::shared_ptr<T>)> fn) = 0;

};

#endif
