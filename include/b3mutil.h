#pragma once

#include <stdint.h>

#define HOST_BIG_ENDIAN

namespace kondo {

  template <typename T>
  void serialize_short(uint8_t* byte_buffer, const T value) {
#ifdef HOST_BIG_ENDIAN
    byte_buffer[0] = (uint8_t)((0x00FF & value));
    byte_buffer[1] = (uint8_t)((0xFF00 & value) >> 8);
#else
    byte_buffer[1] = (uint8_t)((0x00FF & value));
    byte_buffer[0] = (uint8_t)((0xFF00 & value) >> 8);
#endif
  }

  template <typename T>
  void deserialize_short(const uint8_t* byte_buffer, T* out) {
    T value = 0;
#ifdef HOST_BIG_ENDIAN
    value = byte_buffer[1]; value <<= 8;
    value |= byte_buffer[0];
#else
    value = byte_buffer[0]; value <<= 8;
    value |= byte_buffer[1];
#endif
    *out = value;
  }

  template <typename T>
  void serialize_long(uint8_t* byte_buffer, const T value) {
#ifdef HOST_BIG_ENDIAN
    byte_buffer[0] = (uint8_t)((0x000000FF & value));
    byte_buffer[1] = (uint8_t)((0x0000FF00 & value) >> 8);
    byte_buffer[2] = (uint8_t)((0x00FF0000 & value) >> 16);
    byte_buffer[3] = (uint8_t)((0xFF000000 & value) >> 24);
#else
    byte_buffer[3] = (uint8_t)((0x000000FF & value));
    byte_buffer[2] = (uint8_t)((0x0000FF00 & value) >> 8);
    byte_buffer[1] = (uint8_t)((0x00FF0000 & value) >> 16);
    byte_buffer[0] = (uint8_t)((0xFF000000 & value) >> 24);
#endif
  }

  template <typename T>
  void deserialize_long(const uint8_t* byte_buffer, T *out) {
    T value = 0;
#ifdef HOST_BIG_ENDIAN
    value |= byte_buffer[3]; value <<= 8;
    value |= byte_buffer[2]; value <<= 8;
    value |= byte_buffer[1]; value <<= 8;
    value |= byte_buffer[0];
#else
    value |= byte_buffer[0]; value <<= 8;
    value |= byte_buffer[1]; value <<= 8;
    value |= byte_buffer[2]; value <<= 8;
    value |= byte_buffer[3];
#endif
    *out = value;
  }


};

