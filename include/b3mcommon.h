#pragma once


#ifdef WIN32
#ifdef _WINDLL
#define B3MAPI __declspec(dllexport)
#else
#define B3MAPI __declspec(dllimport)
#endif
#else
#define B3MAPI 
#endif


#include <stdint.h>

namespace kondo {
  const uint32_t PACKET_WAIT_SLEEP_TIME = 10; // msec

  const uint32_t DEFAULT_BAUDRATE = 1500000;

  typedef uint8_t ID_t;
  typedef uint8_t address_t;

  enum command_t {
    COMMAND_LOAD = 0x01,
    COMMAND_SAVE = 0x02,
    COMMAND_READ = 0x03,
    COMMAND_WRITE = 0x04,
    COMMAND_RESET = 0x05,
    COMMAND_POSITION = 0x06,

    COMMAND_RECEIVE_MASK = 0x80,
  };

  const uint32_t MAX_DATA_SIZE = 64;

  enum option_t {
    OPTION_ERROR_STATUS = 0x00,
    OPTION_SYSTEM_STATUS = 0x01,
    OPTION_MOTOR_STATUS = 0x02,
    OPTION_UART_STATUS = 0x03,
    OPTION_COMMAND_STATUS = 0x04,
  };
  typedef uint8_t status_t;
};
