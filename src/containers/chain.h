#ifndef TRAITOROUS_CONTAINERS_CHAIN_H
#define TRAITOROUS_CONTAINERS_CHAIN_H

#include <initializer_list>
#include <array>

#include "containers/shared.h"

namespace traitorous {

enum ChainType {
  EMPTY_CHAIN,
  ITEM_CHAIN,
  ARRAY_CHAIN,
  CONCAT_CHAIN,
  SLICE_CHAIN
};

template<class T>
class LocalChain {
public:

  virtual ChainType GetType() const = 0;

  virtual unsigned long Size() const = 0;

};

using Chain = Shared<LocalChain>;

template<class T>
class EmptyChain : public LocalChain<T> {
public:

  ChainType GetType() const {
    return EMPTY_CHAIN;
  };

  unsigned long Size() const {
    return 0;
  }

};

template<class T>
class ItemChain : public LocalChain<T> {

  const T _item;

public:

  ItemChain(const T& item): _item(item) {
    //
  };

  ItemChain(const T&& item): _item(item) {
    //
  };

  ChainType GetType() const {
    return ITEM_CHAIN;
  };

  unsigned long Size() const {
    return 1;
  }

  T Item() const {
    return _item;
  }

};

template<class T, class S>
class ArrayChain : public LocalChain<T> {

  const std::array<T, S> _array;

public:

  ArrayChain(const T& array): _array(array) {
    //
  }

  ArrayChain(const T&& array): _array(array) {
    //
  }

  ChainType GetType() const {
    return ARRAY_CHAIN;
  };

  unsigned long Size() const {
    return _array.size();
  }

  std::array<T, S> Array() const {
    return _array;
  };

};

template<class T>
class ConcatChain : public LocalChain<T> {

  const Chain<T> _left;

  const Chain<T> _right;

public:

  ConcatChain(const Chain<T>& left, const Chain<T>& right): _left(left), _right(right) {
    //
  }

  ChainType GetType() const {
    return CONCAT_CHAIN;
  };

  unsigned long Size() const {
    return _left->Size() + _right->Size();
  }

  Chain<T> Left() const {
    return _left;
  }

  Chain<T> Right() const {
    return _right;
  }

};

template<class T>
class SliceChain : public LocalChain<T> {

  const Chain<T> _chain;

  const uint32_t _offset;

  const uint32_t _length;

public:

  SliceChain(const Chain<T>& chain, uint32_t offset, uint32_t length): _chain(chain),
                                                                       _offset(offset),
                                                                       _length(length)
  {
    //
  }

  ChainType GetType() const {
    return SLICE_CHAIN;
  };

  Chain<T> WrappedChain() const {
    return _chain;
  }

  uint32_t Offset() const {
    return _offset;
  }

  uint32_t Length() const {
    return _length;
  }

};

template<class T>


}

#endif
