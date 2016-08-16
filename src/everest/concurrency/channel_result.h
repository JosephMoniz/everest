#pragma once

#include <everest/containers/option.h>

namespace everest {

template<class T>
class ChannelResult final {

  Option<T> _option;

public:

  ChannelResult() noexcept : _option(Option<T>::None()) { }

  template <class U = T>
  ChannelResult(T value, typename std::enable_if<std::is_pointer<U>::value>::type* = 0) noexcept : _option(value) { }

  ChannelResult(T&& value) noexcept : _option(std::move(value)) { }

  template <class U = T>
  static ChannelResult<T> More(T option, typename std::enable_if<std::is_pointer<U>::value>::type* = 0) noexcept {
    return ChannelResult<T>(option);
  }

  static ChannelResult<T> More(T&& option) noexcept {
    return ChannelResult<T>(std::forward<T>(option));
  }

  static ChannelResult<T> Done() noexcept {
    return ChannelResult<T>();
  }

  const T& Get() const noexcept {
    return _option.Get();
  }

  T&& GetMovable() const noexcept {
    return _option.GetMovable();
  }

  bool IsMore() const noexcept {
    return _option.IsSome();
  }

  bool IsDone() const noexcept {
    return _option.IsNone();
  }

};

}