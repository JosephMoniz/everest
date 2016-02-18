#ifndef TRAITOROUS_CONTAINERS_MONOID_MIN_H
#define TRAITOROUS_CONTAINERS_MONOID_MIN_H

namespace traitorous {

template<class T> 
class LocalMonoidMin {

  const T _value;

public:

  MonoidMin(const T& n): _value(n) {
    //
  }

  MonoidMin(const T&& n): _value(n) {
    //
  }

  constexpr T& value() {
    return _value;
  }

};

template<class T>
using MonoidMin = Shared<LocalMonoidMin<T>>

template<class T> 
MonoidMin<T> MakeMonoidMin(const T& value) {
  return MakeShared<LocalMonoidMin<T>>(value);
}

template<class T>
class Ord<LocalMonoidMin<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const LocalMonoidMin<T>& lhs,
                                    const LocalMonoidMin<T>& rhs) noexcept
  {
    return Compare(lhs.value(), rhs.value());
  }

  static constexpr Ordering Min(const LocalMonoidMin<T>& lhs,
                                const LocalMonoidMin<T>& rhs) noexcept
  {
    return (Compare(lhs, rhs) == GREATER)
      ? rhs
      : lhs;
  }

  static constexpr Ordering Max(const LocalMonoidMin<T>& lhs,
                                const LocalMonoidMin<T>& rhs) noexcept
  {
    return (Compare(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

}

template<class T>
class Zero<LocalMonoidMin<T>> {
public: 

  static constexpr bool exists = true;

  static constexpr LocalMonoidMin<T> Zero() {
    return LocalMonoidMin(Zero<T>());
  }

}

template<class T>
class SemiGroup<LocalMonoidMin<T>> {
public:

  static constexpr bool exists = true;

  static constexpr LocalMonoidMin<T> Add(const LocalMonoidMin<T>& lhs,
                                         const LocalMonoidMin<T>& rhs) noexcept
  {
    return Min(lhs, rhs);
  }

}

template<class T>
class Monoid<LocalMonoidMin<T>> {
public:

  static constexpr bool exists = true;

}

template<class T>
class Shows<LocalMonoidMin<T>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const LocalMonoidMin<T>& n) noexcept {
    return std::string("LocalMonoidMin(") + Shows<T>::Show(n.value()) + ")";
  }

}

}

#endif
