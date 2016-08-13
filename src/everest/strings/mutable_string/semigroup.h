#pragma once

#include <everest/strings/mutable_string.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/Pointable.h>

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
    auto lOccupied = lhs.Occupied() - 1;
    auto occupied  = lOccupied + rhs.Occupied();
    lhs._data.ReserveAtLeast(occupied);
    auto lPointer  = lhs._data.MutablePointer();
    auto rPointer  = rhs.Pointer();
    memcpy(&lPointer[lOccupied], rPointer, rhs.Occupied());
    lhs._length   = lhs.Length() + rhs.Length();
    lhs._occupied = occupied;
    return std::move(lhs);
  }

};

}