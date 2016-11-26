#pragma once

#include <netdb.h>
#include <cstring>

namespace everest {

class NetAddressHints final {

  struct addrinfo _hints;

public:

  static const NetAddressHints TcpClient() noexcept {
    auto instance = NetAddressHints();
    memset(&instance._hints, 0, sizeof(instance._hints));
    instance._hints.ai_family   = PF_UNSPEC;
    instance._hints.ai_socktype = SOCK_STREAM;
    return instance;
  }

  static const NetAddressHints TcpServer() noexcept {
    auto instance = NetAddressHints();
    memset(&instance._hints, 0, sizeof(instance._hints));
    instance._hints.ai_family   = AF_UNSPEC;
    instance._hints.ai_socktype = SOCK_STREAM;
    instance._hints.ai_flags    = AI_PASSIVE;
    return instance;
  }

  const struct addrinfo* Struct() const noexcept {
    return &_hints;
  }

};

}