#pragma once

#include <cerrno>
#include <unistd.h>
#include <stddef.h>
#include <netdb.h>
#include <everest/containers/checked.h>
#include <sys/socket.h>
#include <everest/mutable_containers/mutable_vector.h>
#include <everest/types/int64.h>
#include <everest/types/uint32.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/io/net/net_address_info.h>
#include <everest/io/net/net_address.h>


namespace everest {

class TcpClientSocket final {

  int _socket;

  NetAddress _address;

  TcpClientSocket& SetReadTimeout(long seconds) noexcept {
    struct timeval time { .tv_sec = seconds, .tv_usec = 0 };
    setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&time, sizeof(struct timeval));
    return *this;
  }

  TcpClientSocket& SetWriteTimeout(long seconds) noexcept {
    struct timeval time { .tv_sec = seconds, .tv_usec = 0 };
    setsockopt(_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&time, sizeof(struct timeval));
    return *this;
  }

  using Error = int;

  using SocketBuffer = MutableVector<char>;

public:

  TcpClientSocket(int socket, const NetAddress& address) noexcept : _socket(socket), _address(address) { }

  TcpClientSocket(TcpClientSocket& other) = delete;

  TcpClientSocket(TcpClientSocket&& other) noexcept : _socket(other._socket), _address(other._address) {
    other._socket = -1;
  }

  ~TcpClientSocket() noexcept {
    if (_socket != -1) {
      close(_socket);
    }
  }

  static Checked<Error, TcpClientSocket> Connect(const char* host, const char* port) noexcept {
    return NetAddressInfo::ResolveRemote(host, port).Match(
      [](const auto error) {
        return Checked<Error, TcpClientSocket>::Error(error);
      },
      [](const auto& addresses) {
        for (auto address = addresses.Struct(); address != nullptr; address = address->ai_next) {
          auto clientSocket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
          if (clientSocket != -1) {
            auto connectError = connect(clientSocket, address->ai_addr, address->ai_addrlen);
            if (connectError != -1) {
              return Checked<int, TcpClientSocket>::Ok(TcpClientSocket(clientSocket, NetAddress(address->ai_addr)));
            }
          }
        }
        return Checked<int, TcpClientSocket>::Error(0);
      }
    );
  }

  static Checked<Error, TcpClientSocket> Connect(const String& host, const char* port) noexcept {
    return TcpClientSocket::Connect(host.Pointer(), port);
  }

  Checked<Error, ssize_t> Read(void *pointer, size_t bytes) noexcept {
    ssize_t result = read(_socket, pointer, bytes);
    return result != -1
      ? Checked<int, ssize_t>::Ok(result)
      : Checked<int, ssize_t>::Error(errno);
  }

  Checked<Error, ssize_t> Read(void *pointer, size_t bytes, long timeout) noexcept {
    SetReadTimeout(timeout);
    return Read(pointer, bytes);
  }

  Checked<Error, SocketBuffer> Read(size_t bytes) noexcept {
    auto memory = MutableMemory<char>(bytes);
    auto result = read(_socket, memory.MutablePointer(), bytes);
    return result != 1
      ? Checked<int, MutableVector<char>>::Ok(MutableVector<char>(std::move(memory), (size_t)result))
      : Checked<int, MutableVector<char>>::Error(errno);
  }

  Checked<Error, SocketBuffer> Read(size_t bytes, long timeout) noexcept {
    SetReadTimeout(timeout);
    auto result = Read(bytes);
    SetReadTimeout(MaxValue<int32_t>());
    return result;
  }

  Checked<Error, ssize_t> Write(const void* pointer, size_t bytes) noexcept {
    ssize_t result = send(_socket, pointer, bytes, 0);
    return result != -1
      ? Checked<int, ssize_t>::Ok(result)
      : Checked<int, ssize_t>::Error(errno);
  }

  Checked<Error, ssize_t> Write(const void* pointer, size_t bytes, long timeout) noexcept {
    SetWriteTimeout(timeout);
    auto result = Write(pointer, bytes);
    SetReadTimeout(MaxValue<int32_t>());
    return result;
  }

  Checked<Error, ssize_t> Write(const String& string) noexcept {
    return Write(string.Pointer(), string.Length());
  }

  Checked<Error, ssize_t> Write(const String& string, long timeout) noexcept {
    SetWriteTimeout(timeout);
    auto result = Write(string);
    SetReadTimeout(MaxValue<int32_t>());
    return result;
  }

};

}
