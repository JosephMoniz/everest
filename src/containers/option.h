#ifndef TRAITOROUS_CONTAINERS_OPTION
#define TRAITOROUS_CONTAINERS_OPTION 1

#include <string>
#include <memory>
#include <exception>
#include <stdexcept>

#include "traits/unwrappable.h"
#include "traits/eq.h"
#include "traits/container.h"
#include "traits/zero.h"
#include "traits/show.h"

#include "types/any.h"

template<class S>
class Option : public Unwrappable<std::shared_ptr<S>>,
               public Eq<Option<S>>,
               public Zero<Option<S>>,
               public Container,
               public Show,
               public Any
{ };

template<class S>
class None : public Option<S> {
public:

  None<S>() { }

  virtual std::shared_ptr<S> get_value() {
    throw std::runtime_error("Can't call #get_value() on None");
  }

  virtual bool equals(std::shared_ptr<Option<S>> other) {
    return other->is_empty();
  }

  virtual std::shared_ptr<Option<S>> zero() {
    return std::make_shared<None<S>>();
  }

  virtual std::shared_ptr<UInt> length() {
    return std::make_shared<UInt>(0);
  }

  virtual bool is_empty() {
    return true;
  }

  virtual std::string show() {
    return std::string("None");
  }

};

template<class S>
class Some : public Option<S> {

  std::shared_ptr<S> value;

public:

  Some<S>(std::shared_ptr<S> n) : value(n) { }

  Some<S>(S n) : value(std::make_shared<S>(n)) { }

  virtual std::shared_ptr<S> get_value() {
    return value;
  }

  virtual bool equals(std::shared_ptr<Option<S>> other) {
    if (other->is_empty()) {
      return false;
    } else {
      return this->get_value()->equals(other->get_value());
    }
  }

  virtual std::shared_ptr<Option<S>> zero() {
    return std::make_shared<None<S>>();
  }

  virtual std::shared_ptr<UInt> length() {
    return std::make_shared<UInt>(1);
  }

  virtual bool is_empty() {
    return false;
  }

  virtual std::string show() {
    return std::string("Some(") + this->value->show() + ")";
  }

};

#endif
