#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class ZeroVal {

  typedef ZeroVal<T> base;

public:

  static constexpr bool exists = false;

  static constexpr T Zero() noexcept {
    return base::Zero();
  }

};

template <class T>
class DefaultZeroVal {
public:

  static constexpr bool exists = true;

  static constexpr T Zero() noexcept {
    return T{};
  }

};

template <class T>
constexpr T Zero() noexcept {
  return ZeroVal<T>::Zero();
}

}

#pragma clang diagnostic pop