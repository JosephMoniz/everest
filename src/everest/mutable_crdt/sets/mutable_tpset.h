#pragma once

#include <everest/mutable_containers/mutable_set.h>

namespace everest {

template <class T, template <class> class InnerSetType = MutableSet>
class MutableTwoPhaseSet final {

  using Self = MutableTwoPhaseSet<T>;

  using InnerSet = InnerSetType<T>;

  InnerSet _fresh;

  InnerSet _tombs;

public:

  MutableTwoPhaseSet() noexcept : _fresh(), _tombs() { }

  MutableTwoPhaseSet(const Self& other) = delete;

  MutableTwoPhaseSet(Self&& other) noexcept : _fresh(std::move(other._fresh)),
                                              _tombs(std::move(other._tombs)) { }

  MutableTwoPhaseSet(InnerSet&& fresh, InnerSet&& tombs) noexcept : _fresh(std::move(fresh)),
                                                                    _tombs(std::move(tombs)) { }

  Self& Insert(T&& item) noexcept {
    _fresh.AddInPlace(std::move(item));
    return *this;
  }

  Self& Remove(T&& item) noexcept {
    _tombs.AddInPlace(std::move(item));
    return *this;
  }

  InnerSet Value() const noexcept {
    return _fresh - _tombs;
  }

};

}