#ifndef TRAITOROUS_CORE_TAGGEDUNION
#define TRAITOROUS_CORE_TAGGEDUNION 1

#include <functional>

#include "meta/max.h"

template <class... Xs>
struct tagged_union_helper {};

template <class X, class... Xs>
struct tagged_union_helper<X, Xs...> {

  inline static void destruct(size_t id, void* data) noexcept {
    if (id == typeid(X).hash_code()) {
      reinterpret_cast<X*>(data)->~X();
    } else {
      tagged_union_helper<Xs...>::destruct(id, data);
    }
  }

  inline static void move(size_t id, void* val, void* dest) noexcept {
    if (id == typeid(X).hash_code()) {
      new (dest) X(std::move(*reinterpret_cast<X*>(val)));
    } else {
      tagged_union_helper<Xs...>::move(id, val, dest);
    }
  }

  inline static void copy(size_t id, const void* val, void* dest) noexcept {
    if (id == typeid(X).hash_code()) {
      new (dest) X(*reinterpret_cast<const X*>(val));
    } else {
      tagged_union_helper<Xs...>::copy(id, val, dest);
    }
  }

};

template<>
struct tagged_union_helper<>  {
  inline static void destruct(size_t id, void* data) noexcept {}
  inline static void move(size_t id, void* val, void* dest) noexcept {}
  inline static void copy(size_t id, const void* val, void* dest) noexcept {}
};

template <class T, class... Ts>
struct tagged_union {
private:
  typedef tagged_union_helper<T, Ts...> helper;
  static const size_t data_size  = meta_max<sizeof(Ts)...>::value;
  static const size_t data_align = meta_max<alignof(Ts)...>::value;
  using data_t = typename std::aligned_storage<data_size, data_align>::type;
  size_t type_id;
  data_t data;

  static inline size_t invalid_type() {
    return typeid(void).hash_code();
  }

public:

  tagged_union() : type_id(invalid_type()) {}

  tagged_union(const T& val): type_id(typeid(T).hash_code()) {
    helper::copy(type_id, &val, &data);
  }

  tagged_union(size_t id, void* val): type_id(id) {
    helper::copy(id, val, &data);
  }

  tagged_union(const tagged_union<T, Ts...>& val) : type_id(val.type_id) {
    helper::copy(val.type_id, &val.data, &data);
  }

  tagged_union(tagged_union<T, Ts...>&& val) : type_id(val.type_id) {
    helper::move(val.type_id, &val.data, &data);
  }

  tagged_union<T, Ts...>& operator= (tagged_union<T, Ts...> val) noexcept {
    std::swap(type_id, val.type_id);
    std::swap(data, val.data);
    return *this;
  }

  template<class A>
  constexpr bool is() noexcept {
    return (type_id == typeid(A).hash_code());
  }

  constexpr bool valid() noexcept {
    return (type_id != invalid_type());
  }

  template<class N>
  constexpr N get() noexcept { return *reinterpret_cast<const N*>(&data); }

  ~tagged_union() noexcept { helper::destruct(type_id, &data); }

};

#endif
