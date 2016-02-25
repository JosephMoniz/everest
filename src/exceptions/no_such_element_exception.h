#ifndef TRAITOROUS_EXCEPTIONS_NO_SUCH_ELEMENT_EXCEPTION_H
#define TRAITOROUS_EXCEPTIONS_NO_SUCH_ELEMENT_EXCEPTION_H

#include <exception>

namespace traitorous {

class NoSuchElementException: public std::exception {

  virtual const char* what() const noexcept {
    return "No such element";
  }

};

}

#endif
