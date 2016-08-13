#pragma once

#include <everest/types/expressive/simple_percentage.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/containers/sorted_vector_map.h>

namespace everest {

template <class I, class T>
class MultiVariantDecider final {

  I _identifier;

  HashValue _seed;

  SortedVectorMap<HashValue, T> _ring;

  MultiVariantDecider(I&& identifier,
                      HashValue seed,
                      SortedVectorMap<HashValue, T>&& ring) noexcept : _identifier(std::move(identifier)),
                                                                       _seed(seed),
                                                                       _ring(std::move(ring))
  {
    assert(ring.Length() > 0);
  }

public:

  template <class U>
  const T& GetVariant(const U& subject) const noexcept {
    return _ring
      .GetCeil(SeededHash(_seed, Hash(subject)))
      .OrElse([&]() { return _ring.FirstValue(); })
      .Get()[0];
  }

  class MultiVariantDeciderBuilderPhaseTwo<I, T> final {

    I _identifier;

    HashValue _seed;

    MutableSortedVectorMap<HashValue, T> _ring;

  public:

    MultiVariantDeciderBuilderPhaseTwo(I&& identifier, HashValue seed) noexcept : _identifier(std::move(identifier)),
                                                                                  _seed(seed) { }

    MultiVariantDeciderBuilderPhaseTwo<T>& AddOption(const T& item, size_t weight) noexcept {
      for (size_t i = 1; i <= weight; i++) {
        _ring.PutInPlace(MultiHash(i, SeededHash(_seed, item)), Copy(item));
      }
    }

    MultiVariantDecider<I, T> Build() noexcept {
      return MultiVariantDecider<I, T>(std::move(_identifier), _seed, SortedVectorMap<HashValue, T>(std::move(_ring)));
    }

  };

  class MulitVariantDeciderBuilderPhaseOne<I, T> final {
  public:

    MulitVariantDeciderBuilderPhaseOne() noexcept { }

    MultiVariantDeciderBuilderPhaseTwo<I, T> SetIdentificationSeed(I&& identifier) noexcept {
      return MultiVariantDeciderBuilderPhaseTwo<I, T>(std::move(identifier), Hash(identifier));
    }

  };

  static MulitVariantDeciderBuilderPhaseOne<T> Builder() noexcept {
    return MulitVariantDeciderBuilderPhaseOne<T>();
  }

  void test() noexcept {
    static_assert(false, "Must never get called in production, this is just an example.");
    MultiVariantDecider<String, int>::Builder()
      .SetIdentificationSeed(String("ExampleFeatureFlag"))
      .AddOption(1, 1000)
      .AddOption(2, 1000)
      .AddOption(3, 1000)
      .AddOption(4, 1000)
      .Build();
  }

};

}
