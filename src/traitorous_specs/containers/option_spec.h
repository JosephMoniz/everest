#ifndef TRAITOROUS_OPTION_SPEC_H
#define TRAITOROUS_OPTION_SPEC_H

#include "test/bdd.h"

#include "containers/local_option.h"
#include "functions/identity.h"

namespace traitorous {

void option_specification() {
  describe("An option type", []() {
    it("should have a zero value of local_none()", []() {
      return zero_val<local_option<int>>::zero() == local_none<int>();
    });
    describe("in the case of type local_none", []() {
      it("should return OPTION_NONE when calling get_type()", []() {
        return local_none<int>().get_type() == OPTION_NONE;
      });
      it("should evalute the local_none case when calling match()", []() {
        return match(local_none<int>(),
          []()       { return true; },
          [](auto n) { return false; }
        );
      });
      it("should return false when called with contains()", []() {
        return !contains(42, local_none<int>());
      });
      it("should return 0 when called with length()", []() {
        return length(local_none<int>()) == 0;
      });
      it("should return true when called with is_empty()", []() {
        return is_empty(local_none<int>());
      });
      it("should return true when called with equals() and another local_none", []() {
        return equals(local_none<int>(), local_none<int>());
      });
      it("should return false when called with equals() and a local_some()", []() {
        return !equals(local_none<int>(), local_some(42));
      });
      it("should return true when compared with == and another local_none", []() {
        return local_none<int>() == local_none<int>();
      });
      it("should return false when compared with == and a local_some()", []() {
        return !(local_none<int>() == local_some(42));
      });
      it("should return false when compared with != and another local_none", []() {
        return !(local_none<int>() != local_none<int>());
      });
      it("should return true when compared with != a local_some()", []() {
        return local_none<int>() != local_some(42);
      });
      it("should return a hash value of 0 when called with hashable()");
      it("should return none when called with add() and another local_none()", []() {
        return add(local_none<int>(), local_none<int>()) == local_none<int>();
      });
      it("should return local_some(n) when called with add() and a local_some(n)", []() {
        return add(local_none<int>(), local_some(42)) == local_some(42);
      });
      it("should return local_none() when called with filter()", []() {
        return filter(equals(42), local_none<int>()) == local_none<int>();
      });
      it("should return LESS when passed through cmp() with local_some()", []() {
        return cmp(local_none<int>(), local_some(42)) == LESS;
      });
      it("should return EQUAL when passed through cmp() with another local_none()", []() {
        return cmp(local_none<int>(), local_none<int>()) == EQUAL;
      });
      it("should return local_none() when passed through map()", []() {
        return map(multiply(2), local_none<int>()) == local_none<int>();
      });
      it("should return local_none() when passed through ap()", []() {
        return ap(local_some([](auto n) { return n * 2; }), local_none<int>()) == local_none<int>();
      });
      it("should return none() when passed through alt() with another local_none()", []() {
        return alt(local_none<int>(), local_none<int>()) == local_none<int>();
      });
      it("should return local_some(n) when passed through alt() with local_some(n)", []() {
        return alt(local_none<int>(), local_some(42)) == local_some(42);
      });
      it("should return none() when passed through || with another local_none()", []() {
        return (local_none<int>() || local_none<int>()) == local_none<int>();
      });
      it("should return local_some(n) when passed through || with local_some(n)", []() {
        return (local_none<int>() || local_some(42)) == local_some(42);
      });
      it("should return local_none() when called with flat_map()", []() {
        return flat_map([](auto n) { return local_some(n * 2); }, local_none<int>()) == local_none<int>();
      });
      it("should return none() when called with then() and another local_none", []() {
        return then(local_none<int>(), local_none<int>()) == local_none<int>();
      });
      it("should return local_none() when called with then() and a local_some()", []() {
        return then(local_none<int>(), local_some(42)) == local_none<int>();
      });
      it("should return local_none() when called with mplus() and another none()", []() {
        return mplus(local_none<int>(), local_none<int>()) == local_none<int>();
      });
      it("should return local_some(n) when called with mplus() and another local_some(n)", []() {
        return mplus(local_none<int>(), local_some(42)) == local_some(42);
      });
      it("should return zero when called with fold()", []() {
        return fold(local_none<int>()) == 0;
      });
      it("should return zero when called with foldMap()", []() {
        return fold_map(identity<int>(), local_none<int>()) == 0;
      });
      it("should return init when called with foldr()", []() {
        return foldr(add<int>(), 0, local_none<int>()) == 0;
      });
      it("should return init when called with foldl()", []() {
        return foldl(add<int>(), 0, local_none<int>()) == 0;
      });
      it("should return the alternative when called with get_or_else()", []() {
        return get_or_else([]() { return 12; }, local_none<int>()) == 12;
      });
      it("should return the default when called with get_or_default()", []() {
        return get_or_default(42, local_none<int>()) == 42;
      });
      it("should return the string 'local_none' when called with show()", []() {
        return show(local_none<int>()) == std::string("local_none");
      });
    });
    describe("in the case of type local_some", []() {
      it("should return OPTION_SOME when calling get_type()", []() {
        return local_some(42).get_type() == OPTION_SOME;
      });
      it("should evalute the local_some case when calling match()", []() {
        return match(local_some(42),
          []()       { return false; },
          [](auto n) { return true; }
        );
      });
      it("should return true when calling contains() with a matching item", []() {
        return contains(42, local_some(42));
      });
      it("should return false when calling contains() with a different item", []() {
        return !contains(12, local_some(42));
      });
      it("should return 1 when called with length()", []() {
        return length(local_some(42)) == 1;
      });
      it("should return false when called with is_empty", []() {
        return !is_empty(local_some(42));
      });
      it("should return false when called with equals() and a local_none", []() {
        return is_empty(local_none<int>());
      });
      it("should return false when called with equals() and a different item", []() {
        return !equals(local_some(42), local_none<int>());
      });
      it("should return true when called with equals() and a matching item", []() {
        return equals(local_some(42), local_some(42));
      });
      it("should return false when compared with == and a local_none", []() {
        return !(local_some(42) == local_none<int>());
      });
      it("should return false when compared with == and a different item", []() {
        return !(local_some(42) == local_some(12));
      });
      it("should return true when compared with == with a matching item", []() {
        return local_some(42) == local_some(42);
      });
      it("should return true when compared with != and a local_none", []() {
        return local_some(42) != local_none<int>();
      });
      it("should return true when compared with != and a different item", []() {
        return local_some(42) != local_some(12);
      });
      it("should return false when compared with != and a matching item", []() {
        return !(local_some(42) != local_some(42));
      });
      it("should return the hash of the inner item when called with hashable()");
      it("should return itself when called with add() and a local_none()", []() {
        return add(local_some(42), local_none<int>()) == local_some(42);
      });
      it("should return the sum of values when called with add() and a value", []() {
        return add(local_some(42), local_some(6)) == local_some(48);
      });
      it("should return itself when called with + and a local_none()", []() {
        return local_some(42) + local_none<int>() == local_some(42);
      });
      it("should return the sum of values when called with + and a value", []() {
        return local_some(42) + local_some(6) == local_some(48);
      });
      it("should return local_none() when called with filter() and a non match predicate", []() {
        return filter(equals(12), local_some(42)) == local_none<int>();
      });
      it("should return itself when called with filter() and a matching predicate", []() {
        return filter(equals(42), local_some(42)) == local_some(42);
      });
      it("should return GREATER when called with cmp() and a local_none()", []() {
        return cmp(local_some(42), local_none<int>()) == GREATER;
      });
      it("should return GREATER when called with cmp() and a lesser local_some()", []() {
        return cmp(local_some(42), local_some(8)) == GREATER;
      });
      it("should return EQUAL when called with cmp() and an equal local_some()", []() {
        return cmp(local_some(42), local_some(42)) == EQUAL;
      });
      it("should return LESS when called with cmp() and a greater local_some()", []() {
        return cmp(local_some(42), local_some(100)) == LESS;
      });
      it("should return n * 2 when called with map(*2)", []() {
        return map(multiply(2), local_some(42)) == local_some(84);
      });
      it("should return n * 2 when called with ap(*2)", []() {
        return ap(local_some(multiply(2)), local_some(42)) == local_some(84);
      });
      it("should return itself when called with alt() and another local_some()", []() {
        return alt(local_some(42), local_some(12)) == local_some(42);
      });
      it("should return itself when called with alt() and a local_none()", []() {
        return alt(local_some(42), local_none<int>()) == local_some(42);
      });
      it("should return itself when compared with || and another local_some()", []() {
        return (local_some(42) || local_some(12)) == local_some(42);
      });
      it("should return itself when compared with || and local_none()", []() {
        return (local_some(42) || local_none<int>()) == local_some(42);
      });
      it("should return local_none when called with flat_map() and a function -> none", []() {
        return flat_map([](auto n) { return local_none<int>(); }, local_some(42)) == local_none<int>();
      });
      it("should return n * 2 when called with flat_map and a function -> *2", []() {
        return flat_map([](auto n) { return local_some(n * 2); }, local_some(42)) == local_some(84);
      });
      it("should return the next local_some(n) when called with then()", []() {
        return then(local_some(12), local_some(42)) == local_some(42);
      });
      it("should return local_none() when called with then() and a none()", []() {
        return then(local_some(42), local_none<int>()) == local_none<int>();
      });
      it("should return the inner value when called with fold()", []() {
        return fold(local_some(42)) == 42;
      });
      it("should return the inner value mapped when called with fold_map()", []() {
        return fold_map(identity<int>(), local_some(42)) == 42;
      });
      it("should return the folded value when called with foldr()", []() {
        return foldr(add<int>(), 12, local_some(42)) == 54;
      });
      it("should return the folded value when called with foldl()", []() {
        return foldl(add<int>(), 12, local_some(42)) == 54;
      });
      it("should return the inner value when called with get_or_else()", []() {
        return get_or_else([]() { return 12; }, local_some(42)) == 42;
      });
      it("should return the inner value when called with get_or_default()", []() {
        return get_or_default(12, local_some(42)) == 42;
      });
      it("should return the string 'local_some(n)' when called with show()", []() {
        return show(local_some(42)) == std::string("local_some(42)");
      });
    });
  });
}

}

#endif
