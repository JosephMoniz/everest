#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <utility>

namespace everest {

template <class T>
class MutableAssociative {

  typedef MutableAssociative<T> Base;

public:

  static constexpr bool exists = false;

  template <class K, class V>
  static T& PutInPlace(const K& key, const V& value, T& container) noexcept {
    return Base::PutInPlace(key, value, container);
  }

  static T& PutInPlace(const T& source, T& container) noexcept {
    return Base::PutInPlace(source, container);
  }

  template <class K, class V>
  static V* GetInPlace(const K& key, T& container) noexcept {
    return Base::GetInPlace(key, container);
  };

};

template <class F, class K, class V>
F& PutInPlace(K&& key, V&& value, F& container) noexcept {
  static_assert(MutableAssociative<F>::exists, "T does not implement MutableAssociative");
  return MutableAssociative<F>::PutInPlace(std::move(key), std::move(value), container);
}

template <class F>
F& PutInPlace(F&& source, F& container) noexcept {
  static_assert(MutableAssociative<F>::exists, "T does not implement MutableAssociative");
  return MutableAssociative<F>::PutInPlace(std::move(source), container);
}

template <class K, class T>
auto GetInPlace(const K& key, T& container) noexcept -> decltype(MutableAssociative<T>::GetInPlace(key, container)) {
  static_assert(MutableAssociative<T>::exists, "T does not implement MutableAssociative");
  return MutableAssociative<T>::GetInPlace(key, container);
};

}

#pragma clang diagnostic pop