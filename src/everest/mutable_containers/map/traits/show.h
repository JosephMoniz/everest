#pragma once

#include <everest/mutable_containers/mutable_map.h>
#include <everest/mutable_containers/map/mutable_map_entry.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class K, class V>
class MutableMap;

template <class K, class V>
class Shows<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableMap<K, V>& map) noexcept {
    return map.Show();
  }

};

}