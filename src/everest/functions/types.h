#pragma once

#include <functional>

namespace everest {

template<class T, class R>
using Function = std::function<R(T)>;

template<class T, class U, class R>
using BiFunction = std::function<R(T, U)>;

template<class T>
using Predicate = std::function<bool(T)>;

template<class R>
using Supplier = std::function<R()>;

template<class T>
using Consumer = std::function<void(T)>;

using Thunk = std::function<void()>;

}

