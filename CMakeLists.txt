cmake_minimum_required(VERSION 3.2)
project(traitorous_og)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-return-type -ftemplate-backtrace-limit=0")

include_directories(src)

set(SOURCE_FILES
    src/containers_old/monoids/max.h
    src/containers_old/monoids/min.h
    src/containers_old/identity.h
    src/containers_old/validation.h
    src/core/tagged_union.h
    src/cli/color.h
    src/test/bdd.h
    src/meta/max.h
    src/meta/min.h
    src/meta/nth_arg.h
    src/traits/alternative.h
    src/traits/applicative.h
    src/traits/bit_and.h
    src/traits/bit_or.h
    src/traits/bit_xor.h
    src/traits/bounded.h
    src/traits/containable.h
    src/traits/container.h
    src/traits/disjoinable.h
    src/traits/divide.h
    src/traits/droppable.h
    src/traits/eq.h
    src/traits/filterable.h
    src/traits/foldable.h
    src/traits/functor.h
    src/traits/hashable.h
    src/traits/intersectable.h
    src/traits/monad.h
    src/traits/monad_plus.h
    src/traits/monoid.h
    src/traits/multiply.h
    src/traits/negate.h
    src/traits/one.h
    src/traits/ord.h
    src/traits/remainder.h
    src/traits/semigroup.h
    src/traits/set.h
    src/traits/shift_left.h
    src/traits/shift_right.h
    src/traits/show.h
    src/traits/subtract.h
    src/traits/takeable.h
    src/traits/traversable.h
    src/traits/unwrappable.h
    src/traits/zero.h
    src/types/bool.h
    src/types/int16.h
    src/types/int32.h
    src/types/int64.h
    src/types/int8.h
    src/types/string.h
    src/types/uint16.h
    src/types/uint32.h
    src/types/uint64.h
    src/types/uint8.h
    src/main.cc)

add_executable(traitorous_og ${SOURCE_FILES} src/traitorous_specs/types/bool_spec.h src/traitorous_specs/types/int8_spec.h src/traitorous_specs/types/int16_spec.h src/traitorous_specs/types/int32_spec.h src/traitorous_specs/types/int64_spec.h src/traitorous_specs/types/uint8_spec.h src/traitorous_specs/types/uint16_spec.h src/traitorous_specs/types/uint32_spec.h src/traitorous_specs/types/string_spec.h src/containers/local_option.h src/traitorous_specs/containers/option_spec.h src/containers/list.h src/traitorous_specs/containers/list_spec.h src/containers/shared_ptr.h src/containers/validation.h src/traitorous_specs/containers/validation_spec.h src/functions/identity.h src/containers/option.h)