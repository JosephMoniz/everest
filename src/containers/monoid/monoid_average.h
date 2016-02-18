#ifndef TRAITOROUS_CONTAINERS_MONOID_AVERAGE_H
#define TRAITOROUS_CONTAINERS_MONOID_AVERAGE_H

namespace traitorous {

template<class T> 
class MonoidAverage {

  const T _run;

  const T _count;

public:

  MonoidAverage(const T& n): _value(n), _count(One<T>()) {
    //
  }

  MonoidAverage(const T&& n): _value(n), _count(One<T>()) {
    //
  }

  constexpr T& run() {
    return _run;
  }

  constexpr T& count() {
    return _run;
  }

  constexpr T& value() {
    return _value;
  }

};

}

#endif
