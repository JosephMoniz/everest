#pragma once

#include <everest/containers/mutable/mutable_vector.h>

namespace everest {

template <class T>
class MutableSortedVectorSet final {

  MutableVector<T> _vector;

  MutableSortedVectorSet(MutableVector<T>&& vector) noexcept : _vector(std::move(vector)) { }

public:

  MutableSortedVectorSet() noexcept : _vector() { }

  MutableSortedVectorSet(std::initializer_list<T> list) noexcept {
    // TODO: Use quicksort instead of insertion sort
    _vector.ReserveAtLeast(list.size());
    for (auto it = list.begin(); it != list.end(); it++) {
      AddInPlace(*it);
    }
  }

  MutableSortedVectorSet<T> Copy() const noexcept {
    return MutableSortedVectorSet<T>(_vector.Copy());
  }

  template <class U>
  T* FindInPlace(const U& item) noexcept {
    if (Length() != 0) {
      size_t low   = 0;
      size_t high  = Length() - 1;
      auto pointer = MutablePointer();
      size_t mid;
      while (low < high) {
        mid = (low + high) / 2;
        switch (Compare(pointer[mid], item)) {
          case Ordering::LESS:
            low = mid + 1;
            break;
          case Ordering::EQUAL:
            return &pointer[mid];
          case Ordering::GREATER:
            if (mid == 0) {
              return nullptr;
            } else {
              high = mid - 1;
            }
            break;
        }
      }
      return (low == high && Compare(pointer[low], item) == Ordering::EQUAL)
        ? &pointer[low]
        : nullptr;
    } else {
      return nullptr;
    }
  }

  template <class U>
  const T* Find(const U& item) const noexcept {
    if (Length() != 0) {
      size_t low   = 0;
      size_t high  = Length() - 1;
      auto pointer = Pointer();
      size_t mid;
      while (low < high) {
        mid = (low + high) / 2;
        switch (Compare(pointer[mid], item)) {
          case Ordering::LESS:
            low = mid + 1;
            break;
          case Ordering::EQUAL:
            return &pointer[mid];
          case Ordering::GREATER:
            if (mid == 0) {
              return nullptr;
            } else {
              high = mid - 1;
            }
            break;
        }
      }
      return (low == high && Compare(pointer[low], item) == Ordering::EQUAL)
        ? &pointer[low]
        : nullptr;
    } else {
      return nullptr;
    }
  }

  bool Contains(const T& item) const noexcept {
    return Find(item) != nullptr;
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

}