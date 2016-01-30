#ifndef TRAITOROUS_TYPES_STRING
#define TRAITOROUS_TYPES_STRING 1

namespace traitorous {

enum StringType {
  BASE_STRING,
  CONCAT_STRING,
  SLICED_STRING
};

class String {
public:

  virtual StringType get_type() const = 0;

};

class BaseString : public String {
public:

  StringType get_type() const {
    return BASE_STRING;
  }

};

class ConcatString : public String {
public:

  StringType get_type() const {
    return CONCAT_STRING;
  }

};

class SlicedString : public String {
public:

  StringType get_type() const {
    return SLICED_STRING;
  }

};

template <class B,
          class C,
          class S,
          class R = typename std::result_of<B()>::type>
static constexpr R Match(const String& n, B base, C concat, S sliced) noexcept {
  switch (n.get_type()) {
    case BASE_STRING:   return base(dynamic_cast<const BaseString&>(n));
    case CONCAT_STRING: return concat(dynamic_cast<const ConcatString&>(n));
    case SLICED_STRING: return sliced(dynamic_cast<const SlicedString&>(n));
  }
}

}

#endif
