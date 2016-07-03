#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <utility>

namespace everest {

template <class T>
class Associative {

  typedef Associative<T> Base;

public:

  static constexpr bool exists = false;

  template <class K, class V>
  static T& Put(const K& key, const V& value, T& container) noexcept {
    return Base::Put(key, value, container);
  }

  static T& Put(const T& source, T& container) noexcept {
    return Base::Put(source, container);
  }

  template <class K, class V>
  static V* Get(const K& key, T& container) noexcept {
    return Base::Get(key, container);
  };

};

template <class F, class K, class V>
F& Put(K&& key, V&& value, F&& container) noexcept {
  return Associative<F>::Put(std::move(key), std::move(value), std::forward<F>(container));
}

template <class F>
F& Put(F&& source, F&& container) noexcept {
  return Associative<F>::Put(std::move(source), std::forward<F>(container));
}

template <class K, class T>
auto Get(const K& key, T& container) noexcept -> decltype(Associative<T>::Get(key, container)) {
  return Associative<T>::Get(key, container);
};

}

#pragma clang diagnostic pop