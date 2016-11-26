#pragma once

#include <netdb.h>
#include <everest/containers/checked.h>
#include <everest/io/net/net_address_hints.h>

namespace everest {

class NetAddressInfo final {

  struct addrinfo* _info;

  using Error = int;

public:

  NetAddressInfo() noexcept : _info(nullptr) { }

  NetAddressInfo(struct addrinfo* info) noexcept : _info(info) { }

  NetAddressInfo(const NetAddressInfo& other) = delete;

  NetAddressInfo(NetAddressInfo&& other) noexcept : _info(other._info) {
    other._info = nullptr;
  }

  ~NetAddressInfo() noexcept {
    if (_info != nullptr) {
      freeaddrinfo(_info);
    }
  }

  static const Checked<Error, NetAddressInfo> ResolveRemote(const char* host, const char* port) noexcept {
    auto result    = NetAddressInfo();
    auto hints     = NetAddressHints::TcpClient();
    auto dnsResult = getaddrinfo(host, port, hints.Struct(), &result._info);
    if (dnsResult != 0) {
      return Checked<Error, NetAddressInfo>::Error(dnsResult);
    } else {
      return Checked<Error, NetAddressInfo>::Ok(std::move(result));
    }
  }

  static const Checked<Error, NetAddressInfo> ResolveLocal(const char* port) noexcept {
    auto result    = NetAddressInfo();
    auto hints     = NetAddressHints::TcpServer();
    auto dnsResult = getaddrinfo(nullptr, port, hints.Struct(), &result._info);
    if (dnsResult != 0) {
      return Checked<Error, NetAddressInfo>::Error(dnsResult);
    } else {
      return Checked<Error, NetAddressInfo>::Ok(std::move(result));
    }
  }

  const struct addrinfo* Struct() const noexcept {
    return _info;
  }

};

}