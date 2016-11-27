#pragma once

#include <everest/strings/mutable_string.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class Semigroup<MutableString> final {
public:

  static constexpr bool exists = true;

  static MutableString Add(const MutableString& lhs, const MutableString& rhs) noexcept {
    return lhs.Add(rhs);
  }

  static MutableString Add(MutableString&& lhs, const MutableString& rhs) noexcept {
    return std::move(lhs.AddInPlace(rhs));
  }

};

}