#pragma once

#include <everest/mutable_containers/mutable_map.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template<class K, class V>
class MutableMap;


template <class K, class V>
class Iteration<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableMap<K, V>& container, F function) noexcept {
    container.ForEach(function);
  }

};

}