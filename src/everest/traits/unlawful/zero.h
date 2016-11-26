#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class ZeroVal {

  typedef ZeroVal<T> base;

public:

  static constexpr bool exists = false;

  static T Zero() noexcept {
    static_assert(exists, "T does not implement ZeroVal");
    return base::Zero();
  }

};

template <class T>
class DefaultZeroVal {
public:

  static constexpr bool exists = true;

  static T Zero() noexcept {
    return T{};
  }

};

template <class T>
T Zero() noexcept {
  static_assert(ZeroVal<T>::exists, "T does not implement ZeroVal");
  return ZeroVal<T>::Zero();
}

}

#pragma clang diagnostic pop