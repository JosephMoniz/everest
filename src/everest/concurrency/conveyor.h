#pragma once

#include <everest/functions/types.h>
#include <everest/memory/shared.h>

namespace everest {

template<class E, class T>
class LocalConveyor {

  const Consumer<E> _error;

  const Consumer<T> _convey;

  bool _delivered;

public:

  LocalConveyor(const Consumer<E>& error,
                const Consumer<T>& convey) noexcept : _error(error),
                                                      _convey(convey),
                                                      _delivered(false) { }

  void Convey(const T &item) noexcept {
    if (!_delivered) {
      _delivered = true;
      _convey(item);
    }
  }

  void Error(const E& error) noexcept {
    if (!_delivered) {
      _delivered = true;
      _error(error);
    }
  }

};

template<class E, class T>
using Conveyor = Shared<LocalConveyor<E, T>>;

template<class E, class T>
Conveyor<E, T> MakeConveyor(const Consumer<E>& error, const Consumer<T>& convey) noexcept {
  return MakeShared<LocalConveyor<E, T>>(error, convey);
};

}
