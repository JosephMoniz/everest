#pragma once

#include <everest/containers/map.h>
#include <everest/traits/unlawful/>

namespace everest {

template <class K, class V>
class Map;

template <class K, class V>
class Iteration<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Map<K, V>& container, F function) noexcept {
    container.ForEach(function);
  }

};

}