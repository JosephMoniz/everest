#pragma once

#include <netdb.h>
#include <everest/meta/max.h>
#include <type_traits>

namespace everest {

enum class AddressType {
  IPV4 = 0,
  IPV6,
  UNINITIALIZED
};

class NetAddress final {

  using data_t = typename std::aligned_storage<
    meta_max<sizeof(in_addr_t), sizeof(in6_addr)>::value,
    meta_max<alignof(in_addr_t), alignof(in6_addr)>::value
  >::type;

  AddressType _tag;

  data_t _value;

public:

  NetAddress() noexcept : _tag(AddressType::UNINITIALIZED), _value() { }

  NetAddress(struct sockaddr_storage* address) noexcept : NetAddress((struct sockaddr *)address) { }

  NetAddress(struct sockaddr* address) noexcept {
    if (address->sa_family == AF_INET) {
      _tag = AddressType::IPV4;
      new (&_value) in_addr_t(((struct sockaddr_in*)address)->sin_addr.s_addr);
    } else {
      _tag = AddressType::IPV6;
      new (&_value) in6_addr(((struct sockaddr_in6*)address)->sin6_addr);
    }
  }

  bool IsIPv4() const noexcept {
    return _tag == AddressType::IPV4;
  }

  bool IsIPv6() const noexcept {
    return _tag == AddressType::IPV6;
  }

  const in_addr_t* GetIPv4() const noexcept {
    return (in_addr_t*) &_value;
  }

  const in6_addr* GetIPv6() const noexcept {
    return (in6_addr*) &_value;
  }

  template <class V4, class V6>
  auto Match(V4 v4, V6 v6) const noexcept -> decltype(V4(GetIPv4())) {
    return (IsIPv4())
      ? v4(GetIPv4())
      : v6(GetIPv6());
  }

};

}