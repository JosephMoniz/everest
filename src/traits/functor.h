#ifndef TRAITOROUS_TRAITS_FUNCTOR
#define TRAITOROUS_TRAITS_FUNCTOR 1

template<class T>
class Functor {
public:

  template<class S, class B>
  virtual S map(std::function<B(T)> fn) = 0;

};

#endif
