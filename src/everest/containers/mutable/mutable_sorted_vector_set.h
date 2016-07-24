#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/iteration.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T>
class MutableSortedVectorSet final {

  MutableVector<T> _vector;

public:

  MutableSortedVectorSet() noexcept : _vector() { }

  MutableSortedVectorSet(std::initializer_list<T> list) noexcept {
    // TODO: Use quicksort instead of insertion sort
    _vector.ReserveAtLeast(list.size());
    for (auto it = list.begin(); it != list.end(); it++) {
      AddInPlace(*it);
    }
  }

  bool Contains(const T& item) const noexcept {
    if (Length() != 0) {
      size_t low   = 0;
      size_t high  = Length() -1;
      auto pointer = Pointer();
      size_t mid;
      while (low < high) {
        mid = (low + high) / 2;
        switch (Compare(pointer[mid], item)) {
          case Ordering::LESS:
            low = mid + 1;
            break;
          case Ordering::EQUAL:
            return true;
          case Ordering::GREATER:
            if (mid == 0) {
              return false;
            } else {
              high = mid - 1;
            }
            break;
        }
      }
      return low == high && Compare(pointer[low], item) == Ordering::EQUAL;
    } else {
      return false;
    }
  }

  MutableSortedVectorSet<T>& AddInPlace(const T& item) noexcept {
    if (Length() != 0) {
      size_t low   = 0;
      size_t high  = Length() - 1;
      auto pointer = Pointer();
      size_t mid;
      for (;;) {
        if (high <= low) {
          auto position = (item > pointer[low]) ? (low + 1) : low;
          _vector.InsertInPlace(item, position);
          return *this;
        } else {
          mid = (low + high) / 2;
          switch (Compare(pointer[mid], item)) {
            case Ordering::LESS:
              low = mid + 1;
              break;
            case Ordering::EQUAL:
              // TODO: add in place for maps
              //_vector.At(mid).Get() = item;
              return *this;
            case Ordering::GREATER:
              if (mid == 0) {
                _vector.InsertInPlace(item, 0);
                return *this;
              }
              high = mid - 1;
              break;
          }
        }
      }
    } else {
      _vector.PushInPlace(item);
      return *this;
    }
  }

  MutableSortedVectorSet<T>& AddInPlace(const MutableSortedVectorSet<T>& other) noexcept {
    auto self = this;
    other.ForEach([self](const T& item) {
      self->AddInPlace(item);
    });
  }

  MutableSortedVectorSet<T>& AddInPlace(T&& item) noexcept {
    if (Length() != 0) {
      size_t low   = 0;
      size_t high  = Length() - 1;
      auto pointer = Pointer();
      size_t mid;
      for (;;) {
        if (high <= low) {
          auto position = (item > pointer[low]) ? (low + 1) : low;
          _vector.InsertInPlace(std::move(item), position);
          return *this;
        } else {
          mid = (low + high) / 2;
          switch (Compare(pointer[mid], item)) {
            case Ordering::LESS:
              low = mid + 1;
              break;
            case Ordering::EQUAL:
              // TODO: add in place for maps
              //_vector.At(mid).Get() = std::move(item);
              return *this;
            case Ordering::GREATER:
              if (mid == 0) {
                _vector.InsertInPlace(std::move(item), 0);
                return *this;
              }
              high = mid - 1;
              break;
          }
        }
      }
    } else {
      _vector.PushInPlace(std::move(item));
      return *this;
    }
  }

  MutableSortedVectorSet<T>& AddInPlace(MutableSortedVectorSet<T>& other) noexcept {
    auto self = this;
    other.ForEach([self](T&& item) {
      self->AddInPlace(std::move(item));
    });
  }

  MutableSortedVectorSet<T>& RemoveInPlace(const T& item) noexcept {
    size_t low   = 0;
    size_t high = Length() == 0 ? 0 : Length() -1;
    auto pointer = Pointer();
    size_t mid;
    while (low < high) {
      mid = (low + high) / 2;
      switch (Compare(pointer[mid], item)) {
        case Ordering::LESS:
          low = mid + 1;
          break;
        case Ordering::EQUAL:
          RemoveAtInPlace(mid, _vector);
          return *this;
        case Ordering::GREATER:
          if (mid == 0) {
            return *this;
          } else {
            high = mid - 1;
          }
          break;
      }
    }
    if (low == high && Compare(pointer[low], item) == Ordering::EQUAL) {
      _vector.RemoveAtInPlace(low);
      return *this;
    } else {
      return *this;
    }
  }

  const T* Pointer() const noexcept {
    return _vector.Pointer();
  }

  size_t Length() const noexcept {
    return _vector.Length();
  }

  bool IsEmpty() const noexcept {
    return _vector.IsEmpty();
  }

  template <class F>
  void ForEach(F function) const noexcept {
    _vector.ForEach(function);
  }

  String Show() const noexcept {
    auto out = String("MutableSortedVectorSet(");
    ForEach([&](const T& item) {
      out = std::move(out) + Shows<T>::Show(item) + String(", ");
    });
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

  bool Equals(const MutableSortedVectorSet<T>& other) const noexcept {
    return _vector.Equals(other._vector);
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  MutableSortedVectorSet<B> Map(F f) const noexcept {
    auto result = MutableSortedVectorSet<B>();
    ForEach([&](const T& item) {
      result.AddInPlace(f(item));
    });
    return result;
  }

  template<class Predicate>
  MutableSortedVectorSet<T>& FilterInPlace(Predicate predicate) noexcept {
    _vector.FilterInPlace(predicate);
    return *this;
  }

  MutableSortedVectorSet<T> Add(const MutableSortedVectorSet<T>& rhs) const noexcept {
    auto results = MutableSortedVectorSet<T>();
    ForEach([&](const T& item) {
      results.AddInPlace(item);
    });
    rhs.ForEach([&](const T& item) {
      results.AddInPlace(item);
    });
    return results;
  }

  static MutableSortedVectorSet<T> Zero() noexcept {
    return MutableSortedVectorSet<T>();
  }

};

template <class T>
class Pointable<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const MutableSortedVectorSet<T>& set) noexcept {
    return set.Pointer();
  }

};

template <class T>
class Container<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableSortedVectorSet<T>& set) noexcept {
    return set.Length();
  }

  static bool IsEmpty(const MutableSortedVectorSet<T>& set) noexcept {
    return set.IsEmpty();
  }

};

template <class T>
class Containable<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const MutableSortedVectorSet<T>& set) noexcept {
    return set.Contains(item);
  }

};

template <class T>
class Iteration<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableSortedVectorSet<T>& set, const F& function) noexcept {
    set.ForEach(function);
  }

};

template <class T>
class Shows<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableSortedVectorSet<T>& set) noexcept {
    return set.Show();
  }

};

template<class T>
class Eq<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableSortedVectorSet<T>& lhs, const MutableSortedVectorSet<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template <class T>
class Functor<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableSortedVectorSet<B> Map(F f, const MutableSortedVectorSet<T>& set) noexcept {
    return set.Map(f);
  }

};

template<class T>
class MutableRemove<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorSet<T>& RemoveInPlace(const T& item, MutableSortedVectorSet<T>& set) noexcept {
    return set.RemoveInPlace(item);
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  static MutableSortedVectorSet<T>& RemoveInPlace(const U& source, MutableSortedVectorSet<T>& set) noexcept {
    ForEach(source, [&](const T& item) {
      set.RemoveInPlace(item);
    });
  }

};

template<class T>
class MutableAdd<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorSet<T>& AddInPlace(const T& source, MutableSortedVectorSet<T>& destination) noexcept {
    return destination.AddInPlace(source);
  }

  static MutableSortedVectorSet<T>& AddInPlace(T&& source, MutableSortedVectorSet<T>& destination) noexcept {
    return destination.AddInPlace(std::move(source));
  }

  static MutableSortedVectorSet<T>& AddInPlace(const MutableSortedVectorSet<T>& source,
                                               MutableSortedVectorSet<T>& destination) noexcept
  {
    return destination.AddInPlace(source);
  }

  static MutableSortedVectorSet<T>& AddInPlace(MutableSortedVectorSet<T>&& source,
                                               MutableSortedVectorSet<T>& destination) noexcept
  {
    return destination.AddInPlace(std::move(source));
  }

};

template <class T>
class MutableFilter<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSortedVectorSet<T>& FilterInPlace(Predicate predicate, MutableSortedVectorSet<T>& set) noexcept {
    return set.FilterInPlace(predicate);
  }

};

template<class T>
class Semigroup<MutableSortedVectorSet<T>> final {
public:

static constexpr bool exists = true;

  static MutableSortedVectorSet<T> Add(const MutableSortedVectorSet<T>& lhs,
                                       const MutableSortedVectorSet<T>& rhs) noexcept
  {
    return lhs.Add(rhs);
  }

};

template<class T>
class ZeroVal<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorSet<T> Zero() noexcept {
    return MutableSortedVectorSet<T>::Zero();
  }

};

}