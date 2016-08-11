#pragma once

#include <everest/types/expressive/simple_percentage.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/containers/sorted_vector_map.h>

namespace everest {

template <class T>
class MultiVariantDecider<T> final {

  HashValue _seed;

  SortedVectorMap<HashValue, T> _ring;

public:

  MultiVariantDecider(const T& identifier, SortedVectorMap<HashValue, T>&& ring) noexcept : _seed(Hash(identifier)),
                                                                                            _ring(std::move(ring))
  {
    assert(ring.Length() > 0);
  }

  template <class U>
  const T& GetVariant(const U& subject) const noexcept {
    return _ring
      .GetCeil(SeededHash(_seed, Hash(subject)))
      .OrElse([&]() { return _ring.FirstValue(); })
      .Get()[0];
  }

};

}
