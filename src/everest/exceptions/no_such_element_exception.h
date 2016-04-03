#pragma once

#include <exception>

namespace everest {

class NoSuchElementException: public std::exception {

  virtual const char* what() const noexcept {
    return "No such element";
  }

};

}
