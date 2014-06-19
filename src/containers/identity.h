#ifndef TRAITOROUS_CONTAINERS_IDENTITY
#define TRAITOROUS_CONTAINERS_IDENTITY 1

#include <memory>

namespace traitorous {

template <class T>
struct identity_t {
  T n;

  explicit identity_t(const T& t): n(t) {}

  explicit identity_t(T&& t): n(std::move(t)) {}

  constexpr operator T() const noexcept { return n; }

  constexpr operator const T&() const noexcept { return n; }

  operator T&() noexcept { return n; }

  T& operator*() noexcept { return n; }

  constexpr const T& operator*() const noexcept { return n; }

  T* operator->() noexcept { return std::addressof(n); }

  constexpr const T* operator->() const noexcept { return std::addressof(n); }
  
};

}

#endif
