#ifndef TRAITOROUS_CONTAINERS_ENUMERATORS_OPTION_ENUMERATOR_H
#define TRAITOROUS_CONTAINERS_ENUMERATORS_OPTION_ENUMERATOR_H

#include <containers/option.h>
#include <exceptions/no_such_element_exception.h>

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

  OptionEnumerator(const Option<T>&& option) noexcept : _done(false),
                                                        _option(std::move(option))
  {
    //
  }

  OptionEnumerator(const OptionEnumerator<T>& enumerator) noexcept : _done(enumerator._done),
                                                                     _option(enumerator._option)
  {
    //
  }

  OptionEnumerator(const OptionEnumerator<T>&& enumerator) noexcept : _done(std::move(enumerator._done)),
                                                                      _option(std::move(enumerator._option))

  {
    //
  }

  OptionEnumerator<T>& operator=(const OptionEnumerator<T>& enumerator) noexcept {
    _done   = enumerator._done;
    _option = enumerator._option;
    return *this;
  }

  bool HasNext() const noexcept {
    return !_done && _option->GetType() == OptionType::SOME;
  }

  const T& Next() {
    if (HasNext()) {
      _done = true;
      return _option->Get();
    } else {
      throw NoSuchElementException();
    }
  }

};

}

#endif
