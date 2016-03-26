#ifndef TRAITOROUS_CONTAINERS_CHAIN_H
#define TRAITOROUS_CONTAINERS_CHAIN_H

#include <containers/shared.h>

namespace traitorous {

template<class T>
class LocalChain {

  const T _left;

  const T _right;

public:

  LocalChain(const T& left, const T& right) noexcept : _left(left),
                                                       _right(right) { }

  LocalChain(T&& left, T&& right) noexcept  : _left(std::move(left)),
                                              _right(std::move(right)) { }

  LocalChain(const LocalChain<T>& other) noexcept : _left(other._left),
                                                    _right(other._right) { }

  LocalChain(LocalChain<T>&& other) noexcept : _left(std::move(other._left)),
                                               _right(std::move(other._right)) { }

  LocalChain& operator=(const LocalChain& other) noexcept {
    _left  = other._left;
    _right = other._right;
    return *this;
  }

  LocalChain& operator=(LocalChain&& other) noexcept {
    _left  = std::move(other._left);
    _right = std::move(other._right);
    return *this;
  }

};

template<class T>
using Chain = Shared<LocalChain<T>>;

}

#endif
