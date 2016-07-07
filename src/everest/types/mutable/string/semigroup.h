#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class Semigroup<MutableString> final {
public:

  static constexpr bool exists = true;

  static MutableString Add(const MutableString& lhs, const MutableString& rhs) noexcept {
    auto lOccupied   = Occupied(lhs) - 1;
    auto occupied    = lOccupied + Occupied(rhs);
    auto memory      = MutableMemory<char>(occupied);
    auto lPointer    = Pointer(lhs);
    auto rPointer    = Pointer(rhs);
    auto destPointer = MutablePointer(memory);
    memcpy(destPointer, lPointer, lOccupied);
    memcpy(&destPointer[lOccupied], rPointer, Occupied(rhs));
    return MutableString(std::move(memory), Length(lhs) + Length(rhs), occupied);
  }

  static MutableString Add(MutableString&& lhs, const MutableString& rhs) noexcept {
    auto lOccupied = Occupied(lhs) - 1;
    auto occupied  = lOccupied + Occupied(rhs);
    lhs._data.ReserveAtLeast(occupied);
    auto lPointer  = MutablePointer(lhs._data);
    auto rPointer  = Pointer(rhs);
    memcpy(&lPointer[lOccupied], rPointer, Occupied(rhs));
    lhs._length   = Length(lhs) + Length(rhs);
    lhs._occupied = occupied;
    return std::move(lhs);
  }

};

}