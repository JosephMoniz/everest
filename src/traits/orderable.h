#ifndef TRAITOROUS_TRAITS_ORDERABLE
#define TRAITOROUS_TRAITS_ORDERABLE 1

#include <memory>

#include "ord.h"

template<class S>
class Orderable : public Ord<S> {
public:

  virtual std::shared_ptr<S> min(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> max(std::shared_ptr<S> other) = 0;

};

#endif
