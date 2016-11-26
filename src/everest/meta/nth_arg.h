#pragma once

#include <cstddef>
#include <tuple>

namespace everest {

template <size_t I, typename T>
struct nth_arg : public nth_arg<I, decltype(&T::operator())> { };

template <size_t I, typename ClassType, typename ReturnType, typename... Args>
struct nth_arg<I, ReturnType(ClassType::*)(Args...) const> {

    typedef typename std::tuple_element<I, std::tuple<Args...>>::type type;

};

}