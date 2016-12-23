#pragma once

#include <utility>
#include <everest/strings/string.h>

namespace everest {

template <class I, class O>
class ObjectMatcherVisitor;

template <class I, class O>
class ObjectMatcher {
public:

  virtual O Accept(const ObjectMatcherVisitor<I, O>& visitor) const noexcept = 0;

};

template <class I, class O>
class MatcherEquals;

template <class I, class O>
class MatcherNotEquals;

template <class I, class O>
class MatcherGreaterThan;

template <class I, class O>
class MatcherLessThan;

template <class I, class O>
class MatcherAnd;

template <class I, class O>
class ObjectMatcherVisitor {
public:
  virtual O Equals(const typename I::AttributeKey& key, const String& value) const noexcept = 0;
  virtual O NotEquals(const typename I::AttributeKey& key, const String& value) const noexcept = 0;
  virtual O GreaterThan(const typename I::AttributeKey& key, const String& value) const noexcept = 0;
  virtual O LessThan(const typename I::AttributeKey& key, const String& value) const noexcept = 0;
  virtual O And(const ObjectMatcher<I, O>& left, const ObjectMatcher<I, O>& right) const noexcept = 0;
};

template <class I, class O>
class MatcherEquals : public ObjectMatcher<I, O> {

  const typename I::AttributeKey _key;
  const String _value;

public:

  MatcherEquals(typename I::AttributeKey&& key, String&& value) noexcept : _key(std::move(key)),
                                                                           _value(std::move(value)) { }

  O Accept(const ObjectMatcherVisitor<I, O>& visitor) const noexcept override {
    return visitor.Equals(_key, _value);
  }

};

template <class I, class O>
class MatcherNotEquals : public ObjectMatcher<I, O> {

  const typename I::AttributeKey _key;
  const String _value;

public:

  MatcherNotEquals(typename I::AttributeKey&& key, String&& value) noexcept : _key(std::move(key)),
                                                                              _value(std::move(value)) { }

  O Accept(const ObjectMatcherVisitor<I, O>& visitor) const noexcept override {
    return visitor.NotEquals(_key, _value);
  }

};

template <class I, class O>
class MatcherGreaterThan : public ObjectMatcher<I, O> {

  const typename I::AttributeKey _key;
  const String _value;

public:

  MatcherGreaterThan(typename I::AttributeKey&& key, String&& value) noexcept : _key(std::move(key)),
                                                                                _value(std::move(value)) { }

  O Accept(const ObjectMatcherVisitor<I, O>& visitor) const noexcept override {
    return visitor.GreaterThan(_key, _value);
  }

};

template <class I, class O>
class MatcherLessThan : public ObjectMatcher<I, O> {

  const typename I::AttributeKey _key;
  const String _value;

public:

  MatcherLessThan(typename I::AttributeKey&& key, String&& value) noexcept : _key(std::move(key)),
                                                                             _value(std::move(value)) { }

  O Accept(const ObjectMatcherVisitor<I, O>& visitor) const noexcept override {
    return visitor.LessThan(_key, _value);
  }

};

template <class I, class O>
class MatcherAnd : public ObjectMatcher<I, O> {

  const ObjectMatcher<I, O> _left;
  const ObjectMatcher<I, O> _right;

public:

  MatcherAnd(ObjectMatcher<I, O>&& left, ObjectMatcher<I, O>&& right) noexcept : _left(std::move(left)),
                                                                                 _right(std::move(right)) { }

  O Accept(const ObjectMatcherVisitor<I, O>& visitor) const noexcept override {
    return visitor.And(_left, _right);
  }

};

}