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

  inline static void move(size_t old_t, void * old_v, void * new_v) noexcept {
		if (old_t == typeid(X).hash_code()) {
			new (new_v) X(std::move(*reinterpret_cast<X*>(old_v)));
		} else {
			tagged_union_helper<Xs...>::move(old_t, old_v, new_v);
    }
	}
 
	inline static void copy(size_t old_t, const void * old_v, void * new_v) noexcept {
		if (old_t == typeid(X).hash_code()) {
			new (new_v) X(*reinterpret_cast<const X*>(old_v));
    } else {
			tagged_union_helper<Xs...>::copy(old_t, old_v, new_v);
    }
	}

};

template<>
struct tagged_union_helper<>  {
  inline static void destruct(size_t id, void* data) {}
  inline static void move(size_t old_t, void* old_v, void* new_v) {}
  inline static void copy(size_t old_t, const void* old_v, void* new_v) {}
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

  tagged_union(const T& old): type_id(typeid(T).hash_code()) {
    helper::copy(type_id, &old, &data);
  }

	tagged_union(const tagged_union<T, Ts...>& old) : type_id(old.type_id) {
		helper::copy(old.type_id, &old.data, &data);
	}
 
	tagged_union(tagged_union<T, Ts...>&& old) : type_id(old.type_id) {
		helper::move(old.type_id, &old.data, &data);
	}
 
	tagged_union<T, Ts...>& operator= (tagged_union<T, Ts...> old) noexcept {
		std::swap(type_id, old.type_id);
		std::swap(data, old.data);
		return *this;
	}
 
	template<class A>
	constexpr bool is() noexcept {
		return (type_id == typeid(A).hash_code());
	}
 
	constexpr bool valid() noexcept {
		return (type_id != invalid_type());
	}

  template<class N, class... As>
  void set(As&&... args) {
    helper::destruct(type_id, &data);
    new (&data) N(std::forward<As>(args)...);
    type_id = typeid(N).hash_code();
  }

  
 
  template<class N>
  constexpr N get() noexcept { return *reinterpret_cast<const N*>(&data); }

  ~tagged_union() noexcept { helper::destruct(type_id, &data); }
  
};

#endif
