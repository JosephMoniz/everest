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

  virtual uint64_t long Size() const = 0;

};

template<class T>
using Chain = Shared<LocalChain<T>>;

template<class T>
class EmptyChain : public LocalChain<T> {
public:

  ChainType GetType() const {
    return EMPTY_CHAIN;
  };

  uint64_t Size() const {
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

  uint64_t Size() const {
    return 1;
  }

  T Item() const {
    return _item;
  }

};

template<class T, uint64_t S>
class ArrayChain : public LocalChain<T> {

  T _array[S];

public:

  ArrayChain(std::initializer_list<T> list) {
    std::copy(list.begin(), list.end(), _array);
  }

  ChainType GetType() const {
    return ARRAY_CHAIN;
  };

  uint64_t Size() const {
    return S;
  }

  T* Array() const {
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

  uint64_t Size() const {
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
Chain<T> MakeEmptyChain() {
  return DynamicSharedCast<EmptyChain<T>, LocalChain<T>>(MakeShared<EmptyChain<T>>());
}

template<class T>
Chain<T> MakeItemChain(const T& item) {
  return DynamicSharedCast<ItemChain<T>, LocalChain<T>>(MakeShared<ItemChain<T>>(item));
}

template<class T>
Chain<T> MakeItemChain(const T&& item) {
  return DynamicSharedCast<ItemChain<T>, LocalChain<T>>(MakeShared<ItemChain<T>>(item));
}

template<class T>
Chain<T> MakeArrayChain(std::initializer_list<T> list) {
  return DynamicSharedCast<ArrayChain<T>, LocalChain<T>>(MakeShared<ArrayChain<T, list.size()>>(list));
}

template<class T>
Chain<T> MakeConcatChain(const Chain<T>& left, const Chain<T>& right) {
  return DynamicSharedCast<ConcatChain<T>, LocalChain<T>>(MakeShared<ConcatChain<T>>(left, right));
}

template<class T>
Chain<T> MakeSliceChain(const Chain<T>& inner, uint32_t offset, uint32_t length) {
  return DynamicSharedCast<SliceChain<T>, LocalChain<T>>(MakeShared<SliceChain<T>>(inner, offset, length));
}

template <class T,
          class E,
          class I,
          class A,
          class C,
          class S,
          class R = typename std::result_of<E()>::type>
constexpr R Match(const Chain<T>& chain, E empty, I item, A array, C concat, S slice) noexcept {
  switch (chain->GetType()) {
    case EMPTY_CHAIN:  return empty();
    case ITEM_CHAIN:   return item(DynamicSharedCast<LocalChain<T>, ItemChain<T>>(chain));
    case ARRAY_CHAIN:  return array(DynamicSharedCast<LocalChain<T>, ArrayChain<T>>(chain));
    case CONCAT_CHAIN: return concat(DynamicSharedCast<LocalChain<T>, ConcatChain<T>>(chain));
    case SLICE_CHAIN:  return slice(DynamicSharedCast<LocalChain<T>, SliceChain<T>>(chain));
  }
}

}

#endif
