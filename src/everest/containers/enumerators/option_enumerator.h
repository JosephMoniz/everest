#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/enumerator.h>

namespace traitorous {

template<class T>
class OptionEnumerator {

  bool _done = false;

  SharedOption<T> _option;

public:

  OptionEnumerator(const SharedOption<T>& option) noexcept : _done(false),
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

  static const Option<T> Next(const T& enumerator) noexcept {
    if (!enumerator._done && enumerator._option->GetType() == OptionType::SOME) {
      enumerator._done = true;
      return Option<T>(enumerator._option->Get());
    } else {
      return Option<T>();
    }
  }

};

}
