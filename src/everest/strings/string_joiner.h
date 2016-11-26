#pragma once

#include <everest/traits/unlawful/iteration.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/show.h>
#include <everest/strings/string.h>

namespace everest {

class StringJoiner final {

  String _separator;

public:

  StringJoiner(String&& separator) noexcept : _separator(std::move(separator)) { }

  template <class T, class U>
  String Join(const T& container) noexcept {
    static_assert(Iteration<T>::exists, "T must implement Iteration in order to be Joinable");
    static_assert(Container<T>::exists, "T must implement Container in order to be Joinable");
    static_assert(Shows<T>::exists, "U must implement Shows in order to be Joinable");
    size_t count = 0;
    size_t size  = Container<T>::Length(container);
    if (size > 0) {
      auto builder = String::Builder();
      auto last    = size - 1;
      Iteration<T>::ForEach(container, [&](const U& item) {
        builder.Add(Shows<U>::Show(item));
        if (count++ < last) {
          builder.Add(_separator);
        }
      });
      return builder.Build();
    } else {
      return String("");
    }
  }

};

}