#pragma once

#include <everest/deciders/binary_decider.h>
#include <everest/containers/vector.h>
#include <everest/flags/override/feature_flag_override.h>

namespace everest {

template <class I>
class BinaryFeatureFlag {

  BinaryDecider<String> _decider;

  String _description;

  Vector<FeatureFlagOverride<I, bool>> _overrides;

public:

  BinaryFeatureFlag(BinaryDecider<String>&& decider,
                    String _description,
                    Vector<FeatureFlagOverride<I, bool>>&& overrides) noexcept : _decider(std::move(decider)),
                                                                                 _description(std::move(_description)),
                                                                                 _overrides(std::move(overrides)) { }

  bool IsEnabled(const I& subject) const noexcept {
    return _overrides
      .FoldL(Option::None(), [&](Option<bool>& memo, FeatureFlagOverride<I, bool> override) {
        return (memo.IsEmpty())
          ? override.GetOverride(subject)
          : memo;
      })
      .GetOrElse([&]() { return _decider.IsEnabled(subject); });
  }

  class BinaryFeatureFlagBuilder<I> final {

    BinaryDecider<String>::BinaryDeciderBuilder _decider;

    String _description;

    Vector<FeatureFlagOverride<I, bool>> _overrides;

  public:

    BinaryFeatureFlagBuilder() noexcept : _decider(), _description(), _overrides() { }

    BinaryFeatureFlagBuilder<I>& SetName(String&& name) noexcept {
      _decider.SetIdentificationSeed(std::move(name));
      return *this;
    }

    BinaryFeatureFlagBuilder<I>& SetName(const char* name) noexcept {
      _decider.SetIdentificationSeed(String(name));
      return *this;
    }

    BinaryFeatureFlagBuilder<I>& SetDescription(String&& description) noexcept {
      _description = std::move(description);
      return *this;
    }

    BinaryFeatureFlagBuilder<I>& SetDescription(const char* description) noexcept {
      _description = String(description);
      return *this;
    }

    BinaryFeatureFlagBuilder<I>& SetPercentageEnabled(SimplePercentage percentage) noexcept {
      _decider.SetPercentageEnabled(percentage);
      return *this;
    }

    BinaryFeatureFlagBuilder<I>& SetOverrides(Vector<FeatureFlagOverride<I, bool>>&& overrides) noexcept {
      _overrides = std::move(overrides);
      return *this;
    }

    BinaryFeatureFlag<I> Build() const noexcept {
      return BinaryFeatureFlag<I>(_decider.Build(), std::move(_description), std::move(_overrides));
    }

  };

  static BinaryFeatureFlagBuilder<I> Builder() noexcept {
    return BinaryFeatureFlagBuilder<I>();
  }

};

}