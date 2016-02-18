#ifndef TRAITOROUS_CONTAINERS_ENUMERATOR_H
#define TRAITOROUS_CONTAINERS_ENUMERATOR_H

namespace traitorous {

template<class T>
class Enumerator {
public:

  virtual bool hasNext() = 0;

  virtual T next() = 0;

};

}

#endif
