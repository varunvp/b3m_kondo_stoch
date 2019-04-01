#pragma once

#include "b3mcommon.h"
#include "b3mexception.h"

namespace kondo {
  class Packet {
  public:
    command_t command;
    option_t option;
    ID_t id;
    uint8_t data[MAX_DATA_SIZE];
    uint8_t data_length;

  public:
    status_t status() const {
      return option;
    }

  public:
    uint8_t size() const {
      return 5 + data_length;
    }

  public:
    Packet() {
      data_length = 0;
    }
    ~Packet() {}

  public:
    void serialize(uint8_t *packet_buffer) const {
      uint8_t sum = 0;
      packet_buffer[0] = size();
      packet_buffer[1] = command;
      packet_buffer[2] = option;
      packet_buffer[3] = id;
      sum = size() + command + option + id;
      for (uint32_t i = 0;i < data_length;i++) {
	packet_buffer[4+i] = data[i];
	sum += data[i];
      }
      packet_buffer[4 + data_length] = sum;
    }

    void deserialize(const uint8_t *packet_buffer) {
      uint8_t size = packet_buffer[0];
      uint8_t sum = 0;
      uint8_t id_buf = id;
      command = static_cast<command_t>(packet_buffer[1]);
      option  = static_cast<option_t>(packet_buffer[2]);
      id = packet_buffer[3];
      sum = size + command + option + id;
      data_length = size - 5;
      for(uint32_t i = 0;i < data_length;i++) {
	data[i] = packet_buffer[4 + i];
	sum += data[i];
      }
      if (packet_buffer[4 + data_length] != sum) {
	throw ChecksumException(id_buf, id);
      }
    }
  };


};


