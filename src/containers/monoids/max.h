#ifndef TRAITOROUS_CONTAINERS_MONOIDS_MAX
#define TRAITOROUS_CONTAINERS_MONOIDS_MAX 1

#include <string>
#include <memory>

#include "traits/unwrappable.h"
#include "traits/eq.h"
#include "traits/orderable.h"
#include "traits/bounded.h"
#include "traits/monoid.h"

template<class S>
class Max : public Unwrappable<std::shared_ptr<S>>,
            public Eq<Max<S>>,
            public Orderable<Max<S>>,
            public Bounded<Max<S>>,
            public Monoid<Max<S>>,
            public Show,
            public std::enable_shared_from_this<Max<S>>
{

  std::shared_ptr<S> value;

public:

  Max<S>(std::shared_ptr<S> n) : value(n) { }

  Max<S>(S n) : value(std::make_shared<S>(n)) { }

  virtual std::shared_ptr<S> get_value() {
    return value;
  }

  virtual bool equals(std::shared_ptr<Max<S>> other) {
    return this->get_value()->equals(other->get_value());
  }

  virtual Ordering cmp(std::shared_ptr<Max<S>> other) {
    return this->get_value()->cmp(other->get_value());
  }

  virtual std::shared_ptr<Max<S>> min(std::shared_ptr<Max<S>> other) {
    switch(this->cmp(other)) {
      case LESS:    return other;
      case EQUAL:   return this->shared_from_this();
      case GREATER: return this->shared_from_this();
    }
  }

  virtual std::shared_ptr<Max<S>> max(std::shared_ptr<Max<S>> other) {
    switch(this->cmp(other)) {
      case LESS:    return this->shared_from_this();
      case EQUAL:   return this->shared_from_this();
      case GREATER: return other;
    }
  }

  virtual std::shared_ptr<Max<S>> add(std::shared_ptr<Max<S>> other) {
    return std::make_shared<Max<S>>(this->get_value()->max(other->get_value()));
  }

  virtual std::shared_ptr<Max<S>> min_value() {
    return std::make_shared<Max<S>>(this->get_value()->min_value());
  }

  virtual std::shared_ptr<Max<S>> max_value() {
    return std::make_shared<Max<S>>(this->get_value()->max_value());
  }

  virtual std::shared_ptr<Max<S>> operator+(std::shared_ptr<Max<S>> other) {
    return std::make_shared<Max<S>>(this->get_value()->max(other->get_value()));
  }

  virtual std::shared_ptr<Max<S>> zero() {
    return std::make_shared<Max<S>>(this->get_value()->min_value());
  }

  virtual bool is_zero() {
    return this->get_value()->equals(this->zero()->get_value());
  }

  virtual std::string show() {
    return std::string("Max(") + this->value->show() + ")";
  }

};

#endif
