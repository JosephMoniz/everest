#ifndef TRAITOROUS_TYPES__BASIC_NUM
#define TRAITOROUS_TYPES__BASIC_NUM 1

#include <memory>
#include <string>

#include "traits/unwrappable.h"
#include "traits/eq.h"
#include "traits/orderable.h"
#include "traits/bounded.h"
#include "traits/one.h"
#include "traits/monoid.h"
#include "traits/subtract.h"
#include "traits/multiply.h"
#include "traits/divide.h"
#include "traits/remainder.h"
#include "traits/show.h"

template <class S, class T>
class BasicNum : public Unwrappable<T>,
                 public Eq<S>,
                 public Orderable<S>,
                 public Bounded<S>,
                 public One<S>,
                 public Monoid<S>,
                 public Subtract<S>,
                 public Multiply<S>,
                 public Divide<S>,
                 public Remainder<S>,
                 public Show,
                 public std::enable_shared_from_this<S>
{

  T value;

public:

  BasicNum(T n) : value(n) { }

  virtual T get_value() {
    return value;
  }

  virtual bool equals(std::shared_ptr<S> other) {
    return this->get_value() == other->get_value();
  }

  virtual Ordering cmp(std::shared_ptr<S> other) {
    if (this->get_value() < other->get_value()) {
      return LESS;
    } else if (this->get_value() > other->get_value()) {
      return GREATER;
    } else {
      return EQUAL;
    }
  }

  virtual std::shared_ptr<S> min(std::shared_ptr<S> other) {
    switch(this->cmp(other)) {
      case LESS:    return this->shared_from_this();
      case EQUAL:   return this->shared_from_this();
      case GREATER: return other;
    }
  }

  virtual std::shared_ptr<S> max(std::shared_ptr<S> other) {
    switch(this->cmp(other)) {
      case LESS:    return other;
      case EQUAL:   return this->shared_from_this();
      case GREATER: return this->shared_from_this();
    }
  }

  virtual std::shared_ptr<S> min_value() {
    return std::make_shared<S>(std::numeric_limits<T>::min());
  }

  virtual std::shared_ptr<S> max_value() {
    return std::make_shared<S>(std::numeric_limits<T>::max());
  }

  virtual std::shared_ptr<S> add(std::shared_ptr<S> other) {
    return std::make_shared<S>(this->get_value() + other->get_value());
  }

  virtual std::shared_ptr<S> subtract(std::shared_ptr<S> other) {
    return std::make_shared<S>(this->get_value() - other->get_value());
  }

  virtual std::shared_ptr<S> multiply(std::shared_ptr<S> other) {
    return std::make_shared<S>(this->get_value() * other->get_value());
  }

  virtual std::shared_ptr<S> divide(std::shared_ptr<S> other) {
    return std::make_shared<S>(this->get_value() / other->get_value());
  }

  virtual std::shared_ptr<S> remainder(std::shared_ptr<S> other) {
    return std::make_shared<S>(this->get_value() % other->get_value());
  }

  virtual std::shared_ptr<S> zero() {
    return std::make_shared<S>(0);
  }

  virtual bool is_zero() {
    return this->get_value() == 0;
  }

  virtual std::shared_ptr<S> one() {
    return std::make_shared<S>(1);
  }

  virtual std::shared_ptr<S> negate() {
    return std::make_shared<S>(-this->get_value());
  }

  virtual std::string show() {
    return std::to_string(this->value);
  }

};

#endif
