#pragma once

#include <everest/test/bdd.h>
#include <everest/io/file.h>
#include <everest/io/file/stat.h>
#include <everest/io/memory_mapped_file.h>
#include <everest/io/tcp_client_socket.h>
#include <everest/io/tcp_server_socket.h>

namespace everest {

void TcpServerSpecification() {
  Describe("A TCP Server Socket", []() {
    It("should work", []() {
      auto listenResult = TcpServerSocket::Listen("8080");
      auto serverSocket = listenResult.GetMovable();
      auto acceptResult = serverSocket.Accept();
      auto clientSocket = acceptResult.GetMovable();
      auto readResult   = clientSocket.Read(1024 * 16);
      auto writeResult  = clientSocket.Write(String(
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 14\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello Everest!"
      ));
      PrintLn(String(readResult.GetMovable().Pointer()));
      AssertTrue(writeResult.IsOk());
    });
  });
}

}
