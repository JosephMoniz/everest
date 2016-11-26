#pragma once

#include <everest/mutable_containers/mutable_vector.h>

namespace everest {

template <class T>
class MutableSortedVectorSet final {

  MutableVector<T> _vector;

  MutableSortedVectorSet(MutableVector<T>&& vector) noexcept : _vector(std::move(vector)) { }

public:

  MutableSortedVectorSet() noexcept : _vector() { }

  template <class U>
  MutableSortedVectorSet(U&& element) noexcept : _vector() {
    AddInPlace(std::move(element));
  }

  template <class U, class... U2>
  MutableSortedVectorSet(U&& element, U2&&... elements) noexcept : _vector() {
    AddInPlace(std::move(element), std::move(elements)...);
  };

  void Reserve(size_t size) noexcept {
    _vector.Reserve(size);
  }

  void ReserveAtLeast(size_t size) noexcept {
    _vector.ReserveAtLeast(size);
  }

  MutableSortedVectorSet<T> Copy() const noexcept {
    return MutableSortedVectorSet<T>(_vector.Copy());
  }

  template <class U>
  Option<T*> FindInPlace(const U& item) noexcept {
    auto length = Length();
    if (length != 0) {
      size_t low   = 0;
      size_t high  = length - 1;
      auto pointer = MutablePointer();
      size_t mid;
      while (low < high) {
        mid = (low + high) / 2;
        switch (Compare(pointer[mid], item)) {
          case Ordering::LESS:
            low = mid + 1;
            break;
          case Ordering::EQUAL:
            return Option<T*>::Some(&pointer[mid]);
          case Ordering::GREATER:
            if (mid == 0) {
              return Option<T*>::None();
            } else {
              high = mid - 1;
            }
            break;
        }
      }
      return (low == high && Compare(pointer[low], item) == Ordering::EQUAL)
        ? Option<T*>::Some(&pointer[low])
        : Option<T*>::None();
    } else {
      return Option<T*>::None();
    }
  }

  template <class U>
  Option<const T*> Find(const U& item) const noexcept {
    auto length = Length();
    if (length != 0) {
      size_t low   = 0;
      size_t high  = length - 1;
      auto pointer = Pointer();
      size_t mid;
      while (low < high) {
        mid = (low + high) / 2;
        switch (Compare(pointer[mid], item)) {
          case Ordering::LESS:
            low = mid + 1;
            break;
          case Ordering::EQUAL:
            return Option<const T*>::Some(&pointer[mid]);
          case Ordering::GREATER:
            if (mid == 0) {
              return Option<const T*>::None();
            } else {
              high = mid - 1;
            }
            break;
        }
      }
      return (low == high && Compare(pointer[low], item) == Ordering::EQUAL)
        ? Option<const T*>::Some(&pointer[low])
        : Option<const T*>::None();
    } else {
      return Option<const T*>::None();
    }
  }

  // TODO: Make trait
  // TODO: Make test
  template <class U>
  Option<const T*> FindCeil(const U& item) const noexcept {
    auto length = Length();
    if (length != 0) {
      size_t low   = 0;
      size_t high  = length - 1;
      auto pointer = Pointer();
      size_t mid;
      while (low < high) {
        mid = (low + high) / 2;
        switch (Compare(pointer[mid], item)) {
          case Ordering::LESS:
            low = mid + 1;
            break;
          case Ordering::EQUAL:
            return Option<const T*>::Some(&pointer[mid]);
          case Ordering::GREATER:
            if (mid == 0) {
              return Option<const T*>::None();
            } else {
              high = mid - 1;
            }
            break;
        }
      }
      if (low == high) {
        auto next = low + 1;
        switch (Compare(pointer[low], item)) {
          case Ordering::LESS:
            return next < length
              ? Option<const T*>::Some(&pointer[next])
              : Option<const T*>::None();
          case Ordering::EQUAL:
            return Option<const T*>::Some(&pointer[low]);
          case Ordering::GREATER:
            return Option<const T*>::Some(&pointer[low]);
        }
      } else {
        return Option<const T*>::None();
      }
    } else {
      return Option<const T*>::None();
    }
  }

  // TODO: Make trait
  // TODO: Make test
  template <class U>
  Option<const T*> FindFloor(const U& item) const noexcept {
    auto length = Length();
    if (length != 0) {
      size_t low   = 0;
      size_t high  = length - 1;
      auto pointer = Pointer();
      size_t mid;
      while (low < high) {
        mid = (low + high) / 2;
        switch (Compare(pointer[mid], item)) {
          case Ordering::LESS:
            low = mid + 1;
            break;
          case Ordering::EQUAL:
            return Option<const T*>::Some(&pointer[mid]);
          case Ordering::GREATER:
            if (mid == 0) {
              return Option<const T*>::None();
            } else {
              high = mid - 1;
            }
            break;
        }
      }
      if (low == high) {
        switch (Compare(pointer[low], item)) {
          case Ordering::LESS:
            return Option<const T*>::Some(&pointer[low]);
          case Ordering::EQUAL:
            return Option<const T*>::Some(&pointer[low]);
          case Ordering::GREATER:
            if (low > 0) {
              return Option<const T*>::Some(&pointer[low - 1]);
            } else {
              return Option<const T*>::None();
            }
        }
      } else {
        return Option<const T*>::None();
      }
    } else {
      return Option<const T*>::None();
    }
  }

  // TODO: Make trait
  // TODO: Make test
  Option<const T*> First() const noexcept {
    return IsEmpty()
      ? Option<const T*>::None()
      : Option<const T*>::Some(&Pointer()[0]);
  }

  // TODO: Make trait
  // TODO: Make test
  Option<const T*> Last() const noexcept {
    return IsEmpty()
      ? Option<const T*>::None()
      : Option<const T*>::Some(&Pointer()[Length() - 1]);
  }

  bool Contains(const T& item) const noexcept {
    return Find(item).IsSome();
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
          _vector.InsertInPlace(std::move(item), position);
          return *this;
        } else {
          mid = (low + high) / 2;
          switch (Compare(pointer[mid], item)) {
            case Ordering::LESS:
              low = mid + 1;
              break;
            case Ordering::EQUAL:
              _vector.AtInPlace(mid)[0] = item;
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
              _vector.AtInPlace(mid)[0] = std::move(item);
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

  template <class... T2>
  MutableSortedVectorSet<T>& AddInPlace(T&& source, T2&&... sources) noexcept {
    AddInPlace(std::move(source));
    AddInPlace(std::move(sources)...);
  }

  MutableSortedVectorSet<T>& RemoveInPlace(const T& item) noexcept {
    size_t low   = 0;
    size_t high = Length() == 0 ? 0 : Length() - 1;
    auto pointer = Pointer();
    size_t mid;
    while (low < high) {
      mid = (low + high) / 2;
      switch (Compare(pointer[mid], item)) {
        case Ordering::LESS:
          low = mid + 1;
          break;
        case Ordering::EQUAL:
          _vector.RemoveAtInPlace(mid);
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

  template <class U>
  MutableSortedVectorSet<T>& RemoveSimilarInPlace(const U& item) noexcept {
    size_t low   = 0;
    size_t high = Length() == 0 ? 0 : Length() - 1;
    auto pointer = Pointer();
    size_t mid;
    while (low < high) {
      mid = (low + high) / 2;
      switch (Compare(pointer[mid], item)) {
        case Ordering::LESS:
          low = mid + 1;
          break;
        case Ordering::EQUAL:
          _vector.RemoveAtInPlace(mid);
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

  T* MutablePointer() noexcept {
    return _vector.MutablePointer();
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

  template <class F>
  void MovingForEach(F function) noexcept {
    _vector.MovingForEach(function);
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutableSortedVectorSet(")
      .Add(StringJoiner(", ").Join<MutableSortedVectorSet<T>, T>(*this))
      .Add(")")
      .Build();
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

  MutableSortedVectorSet<T> Intersect(const MutableSortedVectorSet<T>& rhs) const noexcept {
    auto results = MutableSortedVectorSet<T>();
    ForEach([&](const T& item) {
      if (rhs.Contains(item)) {
        results.AddInPlace(item);
      }
    });
    return results;
  }

  MutableSortedVectorSet<T> Subtract(const MutableSortedVectorSet<T>& rhs) const noexcept {
    auto results = MutableSortedVectorSet<T>();
    ForEach([&](const T& item) {
      if (!rhs.Contains(item)) {
        results.AddInPlace(item);
      }
    });
    return results;
  }

  // TODO: Make a trait
  template <class Predicate>
  bool Any(Predicate predicate) const noexcept {
    return _vector.Any(predicate);
  }

  static MutableSortedVectorSet<T> Zero() noexcept {
    return MutableSortedVectorSet<T>();
  }

};

}