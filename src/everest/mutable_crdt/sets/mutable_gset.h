#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>

namespace everest {

template<class T, template <class> class InnerSetType = MutableSet>
class MutableGSet final {

  using Self = MutableGSet<T>;

  using InnerSet = InnerSetType<T>;

  InnerSet _set;

public:

  MutableGSet() noexcept : _set() { }

  MutableGSet(const Self& other) = delete;

  MutableGSet(Self&& other) noexcept : _set(std::move(other._set)) { }

  MutableGSet(InnerSet&& set) noexcept : _set(std::move(set)) { }

  InnerSet& Value() const noexcept {
    return _set;
  }

  Self Add(const Self& rhs) const noexcept {
    return Self(_set + rhs.Value());
  }

  Self& AddInPlace(const Self& rhs) noexcept {
    MutableAdd<InnerSet>::AddInPlace(_set, rhs._set);
    return *this;
  }

  Self& AddInPlace(const T& item) noexcept {
    MutableAdd<InnerSet>::AddInPlace(_set, item);
    return *this;
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutableGSet")
      .Add(Shows<InnerSet>::Show(_set))
      .Add(")")
      .Build();
  }

  bool Equals(const Self& rhs) const noexcept {
    return Eq<InnerSet>::Equals(_set, rhs.Value());
  }

  static Self Zero() {
    return Self();
  }

};

}