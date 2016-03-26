#ifndef TRAITOROUS_CONTAINERS_ENUMERATORS_OPTION_ENUMERATOR_H
#define TRAITOROUS_CONTAINERS_ENUMERATORS_OPTION_ENUMERATOR_H

#include <containers/option.h>
#include <traits/unlawful/enumerator.h>

namespace traitorous {

template<class T>
class OptionEnumerator {

  bool _done = false;

  Option<T> _option;

public:

  OptionEnumerator(const Option<T>& option) noexcept : _done(false),
                                                       _option(option)
  {
    //
  }

  OptionEnumerator(const OptionEnumerator<T>& other) noexcept : _done(other._done),
                                                                _option(other._option)
  {
    //
  }

  OptionEnumerator<T>& operator=(const OptionEnumerator<T>& enumerator) noexcept {
    _done   = enumerator._done;
    _option = enumerator._option;
    return *this;
  }

};

template<class T>
class Enumerator<OptionEnumerator<T>> {
public:

  static constexpr bool exists = true;

  static const LocalOption<T> Next(const T& enumerator) noexcept {
    if (!enumerator._done && enumerator._option->GetType() == OptionType::SOME) {
      enumerator._done = true;
      return LocalOption<T>(enumerator._option->Get());
    } else {
      return LocalOption<T>();
    }
  }

};

}

#endif
