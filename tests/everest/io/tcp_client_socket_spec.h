#pragma once

#include <everest/test/bdd.h>
#include <everest/io/file.h>
#include <everest/io/file/stat.h>
#include <everest/io/memory_mapped_file.h>
#include <everest/io/tcp_client_socket.h>

namespace everest {

void TcpClientSocketSpecification() {
  Describe("A TCP Client Socket", []() {
    Describe("calling Connect(\"www.google.com\", 80)", []() {
      auto connectResult = TcpClientSocket::Connect("www.google.com", "80");
      It("should return a non error response", [&]() {
        AssertTrue(connectResult.IsOk());
      });
      Describe("and then calling Write() with a valid HTTP request", [&]() {
        auto socket = connectResult.GetMovable();
        auto writeResult = socket.Write(
          "GET / HTTP/1.1\r\n"
          "Host: www.google.com\r\n"
          "\r\n"
        );
        It("should return a non error response", [&]() {
          AssertTrue(writeResult.IsOk());
        });
        It("should return that it wrote the correct amount of bytes", [&]() {
          AssertEquals(40, (int)writeResult.Get());
        });
        Describe("and then calling Read()", [&]() {
          auto readResult = socket.Read(1024 * 40);
          It("should return a non error response", [&]() {
            AssertTrue(readResult.IsOk());
          });
          It("should return a valid HTTP response as the result", [&]() {
            AssertEquals(String("HTTP/1.1 200 OK"), String(readResult.GetMovable().MutablePointer()).Take(15));
          });
        });
      });
    });
  });
}

}
