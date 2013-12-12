#ifndef TRAITOROUS_CONTAINERS_MONOIDS_MIN
#define TRAITOROUS_CONTAINERS_MONOIDS_MIN 1

#include <string>
#include <memory>

#include "traits/unwrappable.h"
#include "traits/eq.h"
#include "traits/ord.h"
#include "traits/bounded.h"
#include "traits/monoid.h"

template<class S>
class Min : public Unwrappable<std::shared_ptr<S>>,
            public Eq<Min<S>>,
            public Ord<Min<S>>,
            public Bounded<Min<S>>,
            public Monoid<Min<S>>,
            public Show
{

  std::shared_ptr<S> value;

public:

  Min<S>(std::shared_ptr<S> n) : value(n) { }

  Min<S>(S n) : value(std::make_shared<S>(n)) { }

  virtual std::shared_ptr<S> get_value() {
    return value;
  }

  virtual bool equals(std::shared_ptr<Min<S>> other) {
    return this->get_value()->equals(other->get_value());
  }

  virtual Ordering cmp(std::shared_ptr<Min<S>> other) {
    switch(this->get_value()->cmp(other->get_value())) {
      case LESS:    return GREATER;
      case EQUAL:   return EQUAL;
      case GREATER: return LESS;
    }
  }

  virtual std::shared_ptr<Min<S>> add(std::shared_ptr<Min<S>> other) {
    return std::make_shared<Min<S>>(this->get_value()->min(other->get_value()));
  }

  virtual std::shared_ptr<Min<S>> min_value() {
    return std::make_shared<Min<S>>(this->get_value()->min_value());
  }

  virtual std::shared_ptr<Min<S>> max_value() {
    return std::make_shared<Min<S>>(this->get_value()->max_value());
  }

  virtual std::shared_ptr<Min<S>> operator+(std::shared_ptr<Min<S>> other) {
    return std::make_shared<Min<S>>(this->get_value()->max(other->get_value()));
  }

  virtual std::shared_ptr<Min<S>> zero() {
    return std::make_shared<Min<S>>(this->get_value()->min_value());
  }

  virtual bool is_zero() {
    return this->get_value()->equals(this->zero()->get_value());
  }

  virtual std::string show() {
    return std::string("Min(") + this->value->show() + ")";
  }

};

#endif
