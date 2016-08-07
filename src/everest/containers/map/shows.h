#pragma once

#include <everest/containers/map.h>
#include <everest/traits/unlawful/>

namespace everest {

template <class K, class V>
class Map;

template <class K, class V>
class Shows<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Map<K, V>& map) noexcept {
    return map.Show();
  }

};

}