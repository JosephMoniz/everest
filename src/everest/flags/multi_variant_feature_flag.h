#pragma once

#include <everest/strings/string.h>
#include <everest/deciders/binary_decider.h>
#include <everest/deciders/multi_variant_decider.h>
#include <everest/flags/override/feature_flag_override.h>

namespace everest {

template <class I, class O>
class MultiVariantFeatureFlag {

  MultiVariantDecider<String, O> _decider;

  String _description;

  Vector<FeatureFlagOverride<I, O>> _overrides;

public:

  MultiVariantFeatureFlag(MultiVariantDecider<String, O>&& decider,
                          String _description,
                          Vector<FeatureFlagOverride<I, O>>&& overrides) noexcept : _decider(std::move(decider)),
                                                                                    _description(std::move(_description)),
                                                                                    _overrides(std::move(overrides)) { }

  const O& GetVariant(const I& subject) const noexcept {
    return _overrides
      .FoldL(Option::None(), [&](Option<O&>& memo, FeatureFlagOverride<I, O> override) {
        return (memo.IsEmpty())
          ? override.GetOverride(subject)
          : memo;
      })
      .GetOrElse([&]() { return _decider.GetVariant(subject); });
  }

  class MultiVariantFeatureFlagBuilderPhaseTwo<I, O> final {

    using DeciderBuilder = MultiVariantDecider<String, O>::MultiVariantDeciderBuilderPhaseTwo;

    DeciderBuilder _decider;

    String _description;

    MutableVector<FeatureFlagOverride<I, O>> _overrides;

  public:

    MultiVariantFeatureFlagBuilderPhaseTwo(DeciderBuilder&& decider) noexcept : _decider(std::move(decider)),
                                                                                _description(),
                                                                                _overrides() { }

    MultiVariantFeatureFlagBuilderPhaseTwo<I, O>& SetDescription(String&& description) noexcept {
      _description = std::move(description);
      return *this;
    }

    MultiVariantFeatureFlagBuilderPhaseTwo<I, O>& AddOverride(FeatureFlagOverride<I, O>&& override) noexcept {
      _overrides.AddInPlace(std::move(override));
      return *this;
    }

    MultiVariantFeatureFlagBuilderPhaseTwo<I, O>& AddOption(const O& item, size_t weight) noexcept {
      _decider.AddOption(item, weight);
      return *this;
    }

    MultiVariantFeatureFlag<I, O> Build() noexcept {
      return MultiVariantFeatureFlag<I, O>(
        _decider.Build(),
        std::move(_description),
        Vector(std::move(_overrides))
      );
    }

  };

  class MulitVariantFeatureFlagBuilderPhaseOne<I, O> final {
  public:

    MulitVariantFeatureFlagBuilderPhaseOne() noexcept { }

    MultiVariantFeatureFlagBuilderPhaseTwo<I, O> SetName(I&& name) noexcept {
      return MultiVariantFeatureFlagBuilderPhaseTwo<I, O>(
        MultiVariantDecider<String, O>::Builder()
          .SetIdentificationSeed(std::move(name))
      );
    }

  };

  static MulitVariantFeatureFlagBuilderPhaseOne<I, O> Builder() noexcept {
    return MulitVariantFeatureFlagBuilderPhaseOne<I, O>();
  }

};

}