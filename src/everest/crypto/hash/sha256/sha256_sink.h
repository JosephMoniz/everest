#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/crypto/hash/sha256/sha256_digest.h>
#include <everest/traits/unlawful/funnel.h>

namespace everest {

class Sha256Sink final {

  friend class Sink<Sha256Sink>;

  SHA256_CTX _context;

public:

  Sha256Sink() noexcept {
    SHA256_Init(&_context);
  }

  Sha256Sink& PushThrough(const char* input) noexcept {
    SHA256_Update(&_context, input, strlen(input));
    return *this;
  }

  Sha256Sink& PushThrough(const String& input) noexcept {
    SHA256_Update(&_context, (const unsigned char*)input.Pointer(), input.Occupied());
    return *this;
  }

  Sha256Sink& PushThrough(String&& input) noexcept {
    PushThrough(const_cast<const String&>(input));
    return *this;
  }

  template <class T>
  Sha256Sink& PushThrough(const Memory<T>& input) noexcept {
    SHA256_Update(&_context, (const unsigned char*)input.Pointer(), sizeof(T) * input.Length());
    return *this;
  }

  template <class T>
  Sha256Sink& PushThrough(const MutableMemory<T>& input) noexcept {
    SHA256_Update(&_context, (const unsigned char*)input.Pointer(), sizeof(T) * input.Length());
    return *this;
  }

  template <class T>
  Sha256Sink& PushThrough(const GrowableMemory<T>& input) noexcept {
    SHA256_Update(&_context, (const unsigned char*)input.Pointer(), sizeof(T) * input.Length());
    return *this;
  }

  Sha256Sink& PushThrough(uint8_t number) noexcept {
    SHA256_Update(&_context, &number, sizeof(uint8_t));
    return *this;
  }

  Sha256Sink& PushThrough(uint16_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    return *this;
  }

  Sha256Sink& PushThrough(uint32_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    PushThrough((uint8_t)((number >> 16) & 0xFF));
    PushThrough((uint8_t)((number >> 24) & 0xFF));
    return *this;
  }

  Sha256Sink& PushThrough(uint64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  Sha256Sink& PushThrough(int8_t number) noexcept {
    SHA256_Update(&_context, &number, sizeof(int8_t));
    return *this;
  }

  Sha256Sink& PushThrough(int16_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    return *this;
  }

  Sha256Sink& PushThrough(int32_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    PushThrough((int8_t)((number >> 16) & 0xFF));
    PushThrough((int8_t)((number >> 24) & 0xFF));
    return *this;
  }

  Sha256Sink& PushThrough(int64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  Sha256Sink& PushThrough(size_t size) noexcept {
    size_t bits = sizeof(size) * 8;
    for (size_t i = 0; i < bits; i += 8) {
      PushThrough((int8_t)((size >> i) & 0xFF));
    }
    return *this;
  }

  template <class T>
  Sha256Sink& PushThrough(T&& input) noexcept {
    Funnel<T>::PerformFunnel(input, *this);
    return *this;
  }

  Sha256Digest Hash() noexcept {
    Sha256Digest digest;
    SHA256_Final(MutablePointer(digest), &_context);
    return digest;
  }

};

}

#include <everest/crypto/hash/sha256/sink/sink.h>