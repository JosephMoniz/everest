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

  template <class T, class MutableStringVisitor, class StringVisitor, class ConcatStringVisitor>
  T VisitString(MutableStringVisitor mutableString, StringVisitor string, ConcatStringVisitor concat) noexcept {
    return concat(*this);
  };

};

}