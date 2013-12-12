#ifndef TRAITOROUS_TRAITS_ORD
#define TRAITOROUS_TRAITS_ORD 1

#include <memory>

enum Ordering {
  LESS,
  EQUAL,
  GREATER
};

template<class S>
class Ord : public std::enable_shared_from_this<S> {
public:

  virtual Ordering cmp(std::shared_ptr<S> other) = 0;

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

};

#endif
