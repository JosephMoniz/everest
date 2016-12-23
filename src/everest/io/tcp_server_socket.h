#pragma once

#include <cerrno>
#include <unistd.h>
#include <stddef.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <everest/containers/checked.h>
#include <everest/io/net/net_address_info.h>
#include <everest/io/tcp_client_socket.h>
#include <everest/io/net/net_address.h>
#include <everest/concurrency/channel.h>
#include <thread>

namespace everest {

class TcpServerSocket final {

  int _socket;

  using Error = int;

public:

  using AcceptResult = Checked<Error, TcpClientSocket>;

  TcpServerSocket(int socket) noexcept : _socket(socket) { }

  TcpServerSocket(TcpServerSocket& other) = delete;

  TcpServerSocket(TcpServerSocket&& other) noexcept : _socket(other._socket) {
    other._socket = -1;
  }

  ~TcpServerSocket() noexcept {
    if (_socket != -1) {
      close(_socket);
    }
  }

  static Checked<Error, TcpServerSocket> Listen(const char* port) noexcept {
    return NetAddressInfo::ResolveLocal(port).Match(
      [](const auto error) {
        return Checked<Error, TcpServerSocket>::Error(error);
      },
      [](const auto& addresses) {
        int yes = 1;
        for (auto address = addresses.Struct(); address != nullptr; address = address->ai_next) {
          int sock = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
          if (sock != -1) {
            auto sockOptResult = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
            if (sockOptResult == -1) {
              return Checked<Error, TcpServerSocket>::Error(errno);
            } else {
              if (bind(sock, address->ai_addr, address->ai_addrlen) == -1) {
                close(sock);
              } else {
                if (listen(sock, SOMAXCONN) == -1) {
                  return Checked<Error, TcpServerSocket>::Error(errno);
                } else {
                  return Checked<Error, TcpServerSocket>::Ok(TcpServerSocket(sock));
                }
              }
            }
          }
        }
      }
    );
  }

  AcceptResult Accept() noexcept {
    socklen_t sin_size;
    struct sockaddr_storage their_addr;
    auto remoteSocket = accept(_socket, (struct sockaddr *)&their_addr, &sin_size);
    if (remoteSocket != -1) {
      auto address = NetAddress(&their_addr);
      return Checked<Error, TcpClientSocket>::Ok(TcpClientSocket(remoteSocket, address));
    } else {
      return Checked<Error, TcpClientSocket>::Error(errno);
    }
  }

  class AcceptStreamContainer {

    Channel<AcceptResult> _channel;

    std::thread _thread;

  public:

    AcceptStreamContainer(Channel<AcceptResult>& channel,
                          std::thread&& thread) noexcept : _channel(std::move(channel)),
                                                           _thread(std::move(thread))
    { }

    Channel<AcceptResult>::Stream GetStream() noexcept {
      return _channel.GetStream();
    }

    void Join() noexcept {
      _thread.join();
    }

  };

  AcceptStreamContainer AcceptStream(size_t queueSize) noexcept {
    Channel<AcceptResult> channel(queueSize);
    auto socketFd = _socket;
    auto thread   = std::thread([channel, socketFd]() mutable {
      TcpServerSocket socket(socketFd);
      auto sink   = channel.GetSink();
      while(sink.IsOpen()) {
        sink.PushThrough(socket.Accept());
      }
    });
    return AcceptStreamContainer(channel, std::move(thread));
  }

};

}