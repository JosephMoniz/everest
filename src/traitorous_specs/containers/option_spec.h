#ifndef TRAITOROUS_OPTION_SPEC_H
#define TRAITOROUS_OPTION_SPEC_H

#include "test/bdd.h"

#include "containers/option.h"
#include "functions/identity.h"

namespace traitorous {

void option_specification() {
  describe("An option type", []() {
    it("should have a zero value of none()", []() {
      return zero_val<option<int>>::zero() == none<int>();
    });
    describe("in the case of type none", []() {
      it("should return OPTION_NONE when calling get_type()", []() {
        return none<int>().get_type() == OPTION_NONE;
      });
      it("should evalute the none case when calling match()", []() {
        return match(none<int>(),
          []()       { return true; },
          [](auto n) { return false; }
        );
      });
      it("should return false when called with contains()", []() {
        return !contains(42, none<int>());
      });
      it("should return 0 when called with length()", []() {
        return length(none<int>()) == 0;
      });
      it("should return true when called with is_empty()", []() {
        return is_empty(none<int>());
      });
      it("should return true when called with equals() and another none", []() {
        return equals(none<int>(), none<int>());
      });
      it("should return false when called with equals() and a some()", []() {
        return !equals(none<int>(), some(42));
      });
      it("should return true when compared with == and another none", []() {
        return none<int>() == none<int>();
      });
      it("should return false when compared with == and a some()", []() {
        return !(none<int>() == some(42));
      });
      it("should return false when compared with != and another none", []() {
        return !(none<int>() != none<int>());
      });
      it("should return true when compared with != a some()", []() {
        return none<int>() != some(42);
      });
      it("should return a hash value of 0 when called with hashable()");
      it("should return none when called with add() and another none()", []() {
        return add(none<int>(), none<int>()) == none<int>();
      });
      it("should return some(n) when called with add() and a some(n)", []() {
        return add(none<int>(), some(42)) == some(42);
      });
      it("should return none() when called with filter()", []() {
        return filter(equals(42), none<int>()) == none<int>();
      });
      it("should return LESS when passed through cmp() with some()", []() {
        return cmp(none<int>(), some(42)) == LESS;
      });
      it("should return EQUAL when passed through cmp() with another none()", []() {
        return cmp(none<int>(), none<int>()) == EQUAL;
      });
      it("should return none() when passed through map()", []() {
        return map(multiply(2), none<int>()) == none<int>();
      });
      it("should return none() when passed through ap()", []() {
        return ap(some([](auto n) { return n * 2; }), none<int>()) == none<int>();
      });
      it("should return none() when passed through alt() with another none()", []() {
        return alt(none<int>(), none<int>()) == none<int>();
      });
      it("should return some(n) when passed through alt() with some(n)", []() {
        return alt(none<int>(), some(42)) == some(42);
      });
      it("should return none() when passed through || with another none()", []() {
        return (none<int>() || none<int>()) == none<int>();
      });
      it("should return some(n) when passed through || with some(n)", []() {
        return (none<int>() || some(42)) == some(42);
      });
      it("should return none() when called with flat_map()", []() {
        return flat_map([](auto n) { return some(n * 2); }, none<int>()) == none<int>();
      });
      it("should return none() when called with then() and another none", []() {
        return then(none<int>(), none<int>()) == none<int>();
      });
      it("should return none() when called with then() and a some()", []() {
        return then(none<int>(), some(42)) == none<int>();
      });
      it("should return none() when called with mplus() and another none()", []() {
        return mplus(none<int>(), none<int>()) == none<int>();
      });
      it("should return some(n) when called with mplus() and another some(n)", []() {
        return mplus(none<int>(), some(42)) == some(42);
      });
      it("should return zero when called with fold()", []() {
        return fold(none<int>()) == 0;
      });
      it("should return zero when called with foldMap()", []() {
        return fold_map(identity<int>(), none<int>()) == 0;
      });
      it("should return init when called with foldr()", []() {
        return foldr(add<int>(), 0, none<int>()) == 0;
      });
      it("should return init when called with foldl()", []() {
        return foldl(add<int>(), 0, none<int>()) == 0;
      });
      it("should return the alternative when called with get_or_else()", []() {
        return get_or_else([]() { return 12; }, none<int>()) == 12;
      });
      it("should return the default when called with get_or_default()", []() {
        return get_or_default(42, none<int>()) == 42;
      });
      it("should return the string 'none' when called with show()", []() {
        return show(none<int>()) == std::string("none");
      });
    });
    describe("in the case of type some", []() {
      it("should return OPTION_SOME when calling get_type()", []() {
        return some(42).get_type() == OPTION_SOME;
      });
      it("should evalute the some case when calling match()", []() {
        return match(some(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
      });
      it("should return true when calling contains() with a matching item", []() {
        return contains(42, some(42));
      });
      it("should return false when calling contains() with a different item", []() {
        return !contains(12, some(42));
      });
      it("should return 1 when called with length()", []() {
        return length(some(42)) == 1;
      });
      it("should return false when called with is_empty", []() {
        return !is_empty(some(42));
      });
      it("should return false when called with equals() and a none", []() {
        return is_empty(none<int>());
      });
      it("should return false when called with equals() and a different item", []() {
        return !equals(some(42), none<int>());
      });
      it("should return true when called with equals() and a matching item", []() {
        return equals(some(42), some(42));
      });
      it("should return false when compared with == and a none", []() {
        return !(some(42) == none<int>());
      });
      it("should return false when compared with == and a different item", []() {
        return !(some(42) == some(12));
      });
      it("should return true when compared with == with a matching item", []() {
        return some(42) == some(42);
      });
      it("should return true when compared with != and a none", []() {
        return some(42) != none<int>();
      });
      it("should return true when compared with != and a different item", []() {
        return some(42) != some(12);
      });
      it("should return false when compared with != and a matching item", []() {
        return !(some(42) != some(42));
      });
      it("should return the hash of the inner item when called with hashable()");
      it("should return itself when called with add() and a none()", []() {
        return add(some(42), none<int>()) == some(42);
      });
      it("should return the sum of values when called with add() and a value", []() {
        return add(some(42), some(6)) == some(48);
      });
      it("should return itself when called with + and a none()", []() {
        return some(42) + none<int>() == some(42);
      });
      it("should return the sum of values when called with + and a value", []() {
        return some(42) + some(6) == some(48);
      });
      it("should return none() when called with filter() and a non match predicate", []() {
        return filter(equals(12), some(42)) == none<int>();
      });
      it("should return itself when called with filter() and a matching predicate", []() {
        return filter(equals(42), some(42)) == some(42);
      });
      it("should return GREATER when called with cmp() and a none()", []() {
        return cmp(some(42), none<int>()) == GREATER;
      });
      it("should return GREATER when called with cmp() and a lesser some()", []() {
        return cmp(some(42), some(8)) == GREATER;
      });
      it("should return EQUAL when called with cmp() and an equal some()", []() {
        return cmp(some(42), some(42)) == EQUAL;
      });
      it("should return LESS when called with cmp() and a greater some()", []() {
        return cmp(some(42), some(100)) == LESS;
      });
      it("should return n * 2 when called with map(*2)", []() {
        return map(multiply(2), some(42)) == some(84);
      });
      it("should return n * 2 when called with ap(*2)", []() {
        return ap(some(multiply(2)), some(42)) == some(84);
      });
      it("should return itself when called with alt() and another some()", []() {
        return alt(some(42), some(12)) == some(42);
      });
      it("should return itself when called with alt() and a none()", []() {
        return alt(some(42), none<int>()) == some(42);
      });
      it("should return itself when compared with || and another some()", []() {
        return (some(42) || some(12)) == some(42);
      });
      it("should return itself when compared with || and none()", []() {
        return (some(42) || none<int>()) == some(42);
      });
      it("should return none when called with flat_map() and a function -> none", []() {
        return flat_map([](auto n) { return none<int>(); }, some(42)) == none<int>();
      });
      it("should return n * 2 when called with flat_map and a function -> *2", []() {
        return flat_map([](auto n) { return some(n * 2); }, some(42)) == some(84);
      });
      it("should return the next some(n) when called with then()", []() {
        return then(some(12), some(42)) == some(42);
      });
      it("should return none() when called with then() and a none()", []() {
        return then(some(42), none<int>()) == none<int>();
      });
      it("should return the inner value when called with fold()", []() {
        return fold(some(42)) == 42;
      });
      it("should return the inner value mapped when called with fold_map()", []() {
        return fold_map(identity<int>(), some(42)) == 42;
      });
      it("should return the folded value when called with foldr()", []() {
        return foldr(add<int>(), 12, some(42)) == 54;
      });
      it("should return the folded value when called with foldl()", []() {
        return foldl(add<int>(), 12, some(42)) == 54;
      });
      it("should return the inner value when called with get_or_else()", []() {
        return get_or_else([]() { return 12; }, some(42)) == 42;
      });
      it("should return the inner value when called with get_or_default()", []() {
        return get_or_default(12, some(42)) == 42;
      });
      it("should return the string 'some(n)' when called with show()", []() {
        return show(some(42)) == std::string("some(42)");
      });
    });
  });
}

}

#endif
