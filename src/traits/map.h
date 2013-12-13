#ifndef TRAITOROUS_TRAITS_MAP
#define TRAITOROUS_TRAITS_MAP 1

#include <memory>

#include "containers/option.h"

template<template<class, class> class S, class K, class V>
class Map {
public:

  virtual std::shared_ptr<Option<V>> get(std::shared_ptr<K> key) = 0;

  virtual bool has(std::shared_ptr<K> key) = 0;

  virtual std::shared_ptr<S<K, V>> assoc(std::shared_ptr<K> key,
                                         std::shared_ptr<V> value) = 0;

  virtual std::shared_ptr<S<K, V>> dissoc(std::shared_ptr<K> key) = 0;

};

#endif
