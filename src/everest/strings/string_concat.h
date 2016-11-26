#pragma once

#include <utility>

namespace everest {

template <class L, class R>
class StringConcat final {

  L _left;

  R _right;

public:

  StringConcat(L&& left, R&& right) noexcept : _left(std::move(left)),
                                               _right(std::move(right)) { }

  L& Left() noexcept {
    return _left;
  }

  R& Right() noexcept {
    return _right;
  }

  template <class F>
  void VisitByteSlice(F visitor) const noexcept {
    _left.VisitByteSlice(visitor);
    _right.VisitByteSlice(visitor);
  };

};

}