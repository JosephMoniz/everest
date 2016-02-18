#ifndef TRAITOROUS_CONTAINERS_MONOID_MAX_H
#define TRAITOROUS_CONTAINERS_MONOID_MAX_H

namespace traitorous {

template<class T> 
class MonoidMax {

  const T _value;

public:

  MonoidMax(const T& n): _value(n) {
    //
  }

  MonoidMax(const T&& n): _value(n) {
    //
  }

  constexpr T& value() {
    return _value;
  }

};

template<class T>
using MonoidMax = Shared<LocalMonoidMax<T>>

template<class T> 
MonoidMax<T> MakeMonoidMax(const T& value) {
  return MakeShared<LocalMonoidMax<T>>(value);
}

template<class T>
class Ord<LocalMonoidMax<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const LocalMonoidMax<T>& lhs,
                                    const LocalMonoidMax<T>& rhs) noexcept
  {
    return Compare(lhs.value(), rhs.value());
  }

  static constexpr Ordering Min(const LocalMonoidMax<T>& lhs,
                                const LocalMonoidMax<T>& rhs) noexcept
  {
    return (Compare(lhs, rhs) == GREATER)
      ? rhs
      : lhs;
  }

  static constexpr Ordering Max(const LocalMonoidMax<T>& lhs,
                                const LocalMonoidMax<T>& rhs) noexcept
  {
    return (Compare(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

}

template<class T>
class Zero<LocalMonoidMax<T>> {
public: 

  static constexpr bool exists = true;

  static constexpr LocalMonoidMax<T> Zero() {
    return LocalMonoidMax(Zero<T>());
  }

}

template<class T>
class SemiGroup<LocalMonoidMax<T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalMonoidMax<T> Add(const LocalMonoidMax<T>& lhs,
                                         const LocalMonoidMax<T>& rhs) noexcept
  {
    return Max(lhs, rhs);
  }

}

template<class T>
class Monoid<LocalMonoidMax<T>> {
public:

  static constexpr bool exists = true;

}

template<class T>
class Shows<LocalMonoidMax<T>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const LocalMonoidMax<T>& n) noexcept {
    return std::string("LocalMonoidMax(") + Shows<T>::Show(n.value()) + ")";
  }

}

}

#endif
