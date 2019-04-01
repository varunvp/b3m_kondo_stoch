#pragma once


namespace kondo {

  static const uint8_t OPERATION_MODE_NORMAL = 0x00;
  static const uint8_t OPERATION_MODE_FREE = 0x02;
  static const uint8_t OPERATION_MODE_HOLD = 0x03;

  static const uint8_t CONTROL_MODE_POSITION    = 0x00 << 2;
  static const uint8_t CONTROL_MODE_VELOCITY    = 0x01 << 2;
  static const uint8_t CONTROL_MODE_TORQUE      = 0x02 << 2;
  static const uint8_t CONTROL_MODE_FEEDFORWARD = 0x03 << 2;

  static const uint8_t ADDRESS_MODE = 0x28;
  static const uint8_t ADDRESS_TARGET_POSITION = 0x2A;
  static const uint8_t ADDRESS_ACTUAL_POSITION = 0x2C;
  static const uint8_t ADDRESS_TARGET_VELOCITY = 0x30;
  static const uint8_t ADDRESS_ACTUAL_VELOCITY = 0x32;
  static const uint8_t ADDRESS_TARGET_CURRENT = 0x3C;

  static const uint8_t ADDRESS_ENCODER_COUNT = 0x50;
  static const uint8_t ADDRESS_ENCODER_TOTAL_COUNT = 0x52;
  
  static const uint8_t ADDRESS_GAIN_PRESET_NUMBER = 0x5C;
  static const uint8_t ADDRESS_PGAIN0 = 0x5E;
  static const uint8_t ADDRESS_DGAIN0 = 0x62;
  static const uint8_t ADDRESS_IGAIN0 = 0x66;
  static const uint8_t ADDRESS_STATIC_U0 = 0x6A;
  static const uint8_t ADDRESS_DYNAMIC_U0 = 0x6C;
  static const uint8_t ADDRESS_PGAIN1 = 0x6E;
  static const uint8_t ADDRESS_DGAIN1 = 0x72;
  static const uint8_t ADDRESS_IGAIN1 = 0x76;
  static const uint8_t ADDRESS_STATIC_U1 = 0x7A;
  static const uint8_t ADDRESS_DYNAMIC_U1 = 0x7C;
  static const uint8_t ADDRESS_PGAIN2 = 0x7E;
  static const uint8_t ADDRESS_DGAIN2 = 0x82;
  static const uint8_t ADDRESS_IGAIN2 = 0x86;
  static const uint8_t ADDRESS_STATIC_U2 = 0x8A;
  static const uint8_t ADDRESS_DYNAMIC_U2 = 0x8C;

  static const uint8_t ADDRESS_MCU_TEMPERATURE = 0x44;
  static const uint8_t ADDRESS_MOTOR_TEMPERATURE = 0x46;
  static const uint8_t ADDRESS_MOTOR_CURRENT = 0x46;


};
