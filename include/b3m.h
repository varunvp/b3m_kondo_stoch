#pragma once

#include "b3mcommon.h"
#include "b3mutil.h"
#include "b3mpacket.h"
#include "b3mexception.h"

#include "b3mdefines.h"

#include "SerialPort.h"
#include "Thread.h"
    
namespace kondo {
  /**
   * Class for KONDO B3M series.
   */
  class B3MAPI B3M {
  private:
    /**
     * Serial Port Utility Class object.
     */
    ssr::SerialPort* m_pSerialPort;
    
    /**
     * Byte buffer for packet sending/receiving
     */
    uint8_t m_pPacketBuffer[MAX_DATA_SIZE+4];

    ssr::Mutex m_PacketMutex;

    Packet m_Packet;
  public:

    /**
     * Constructor
     * @param filename Filename of SerialPort.
     * @param baudrate BaudRate for SerialPort.
     */
    B3M(const std::string& filename, const int32_t baudrate=DEFAULT_BAUDRATE);

    /**
     * Destructor
     */
    ~B3M();


  private:
    
    void sendPacket(const Packet& packet);

    void receivePacket(Packet* packet);

    void checkError(const ID_t id, const option_t option, const status_t status);

  private:
    /**
     * Basic Command Function LOAD
     */
    void load(const ID_t id);

    /**
     * Basic Command Function SAVE
     */
    void save(const ID_t id);

    /**
     * Basic Command Function READ
     */
    void read(const ID_t id, const address_t address, const uint8_t length, uint8_t *buffer);

    /**
     * Basic Command Function WRITE
     */
    void write(const ID_t id, const address_t address, const uint8_t length, const uint8_t *buffer);

    /**
     * Basic Command Function RESET
     */
    void reset(const ID_t id);

    /**
     * Basic Command Function POSITION
     */
    void position(const ID_t id, const int16_t pos, const uint16_t time);

  private:
    /**
     * Utility Function of Write 2byte data
     */
    template<typename T>
    void writeShort(const ID_t id, const address_t address, const T value) {
      uint8_t buf[2];
      serialize_short<T>(buf, value);
      write(id, address, 2, buf);
    }

    /**
     * Utility Function of Read 2byte data
     */
    template<typename T> T readShort(const ID_t id, const address_t address) {
      uint8_t buf[2];
      T value;
      read(id, address, 2, buf);
      deserialize_short<T>(buf, &value);
      return value;
    }

    /**
     * Utility Function of Write 4byte data
     */
    template<typename T>
    void writeLong(const ID_t id, const address_t address, const T value) {
      uint8_t buf[4];
      serialize_long<T>(buf, value);
      write(id, address, 4, buf);
    }

    /**
     * Utility Function of Read 4byte data
     */
    template<typename T> T readLong(const ID_t id, const address_t address) {
      uint8_t buf[4];
      T value;
      read(id, address, 4, buf);
      deserialize_long<T>(buf, &value);
      return value;
    }

  public:
    
    /**
     * Set Operation Mode and Control Mode together
     * 
     * Operation Modes:
     * static const uint8_t OPERATION_MODE_NORMAL = 0x00;
     * static const uint8_t OPERATION_MODE_FREE = 0x02;
     * static const uint8_t OPERATION_MODE_HOLD = 0x03;
     *
     * Control Modes:
     * static const uint8_t CONTROL_MODE_POSITION    = 0x00 << 2;
     * static const uint8_t CONTROL_MODE_VELOCITY    = 0x01 << 2;
     * static const uint8_t CONTROL_MODE_TORQUE      = 0x02 << 2;
     * static const uint8_t CONTROL_MODE_FEEDFORWARD = 0x03 << 2;
     *
     * @param id ID number of motor
     * @param mode Combination of Operation Mode and Control Mode.
     *
     * @example setMode(0, OPERATION_MODE_NORMAL | CONTROL_MODE_POSITION);
     */
    void setMode(const ID_t id, const uint8_t mode) {
      write(id, ADDRESS_MODE, 1, &mode);
    }

    /**
     * Set Gain Preset Number
     * @param ID id
     * @param number Preset Number [0,1,2]
     */
    void setGainPresetNumber(const ID_t id, const uint8_t number) {
      write(id, ADDRESS_GAIN_PRESET_NUMBER, 1, &number);
    }

    /**
     * Set Control Gain 0
     * @param ID id
     * @param Kp Proportinal Gain
     * @param Kd Derivative Gain
     * @param Ki Integral Gain
     */
    void setGain0(const ID_t id, const uint32_t Kp, const uint32_t Kd, const uint32_t Ki) {
      writeLong<uint32_t>(id, ADDRESS_PGAIN0, Kp);
      writeLong<uint32_t>(id, ADDRESS_DGAIN0, Kd);
      writeLong<uint32_t>(id, ADDRESS_IGAIN0, Ki);
    }

    void setMyu0(const ID_t id, const uint16_t staticMyu, const uint16_t dynamicMyu) {
      writeShort<uint16_t>(id, ADDRESS_STATIC_U0, staticMyu);
      writeShort<uint16_t>(id, ADDRESS_DYNAMIC_U0, dynamicMyu);
    }

    /**
     * Set Control Gain 1
     * @param ID id
     * @param Kp Proportinal Gain
     * @param Kd Derivative Gain
     * @param Ki Integral Gain
     */
    void setGain1(const ID_t id, const uint32_t Kp, const uint32_t Kd, const uint32_t Ki) {
      writeLong<uint32_t>(id, ADDRESS_PGAIN1, Kp);
      writeLong<uint32_t>(id, ADDRESS_DGAIN1, Kd);
      writeLong<uint32_t>(id, ADDRESS_IGAIN1, Ki);
    }

    void setMyu1(const ID_t id, const uint16_t staticMyu, const uint16_t dynamicMyu) {
      writeShort<uint16_t>(id, ADDRESS_STATIC_U1, staticMyu);
      writeShort<uint16_t>(id, ADDRESS_DYNAMIC_U1, dynamicMyu);
    }

    /**
     * Set Control Gain 2
     * @param ID id
     * @param Kp Proportinal Gain
     * @param Kd Derivative Gain
     * @param Ki Integral Gain
     */
    void setGain2(const ID_t id, const uint32_t Kp, const uint32_t Kd, const uint32_t Ki) {
      writeLong<uint32_t>(id, ADDRESS_PGAIN2, Kp);
      writeLong<uint32_t>(id, ADDRESS_DGAIN2, Kd);
      writeLong<uint32_t>(id, ADDRESS_IGAIN2, Ki);
    }

    void setMyu2(const ID_t id, const uint16_t staticMyu, const uint16_t dynamicMyu) {
      writeShort<uint16_t>(id, ADDRESS_STATIC_U2, staticMyu);
      writeShort<uint16_t>(id, ADDRESS_DYNAMIC_U2, dynamicMyu);
    }

    /**
     * Receive Proportional Gain 0
     * @param id ID
     * @return GAin
     */
    uint32_t getKp0(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_PGAIN0); }

    /**
     * Receive Derivative Gain 0
     * @param id ID
     * @return GAin
     */
    uint32_t getKd0(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_DGAIN0); }

    /**
     * Receive Integral Gain 0
     * @param id ID
     * @return Gain
     */
    uint32_t getKi0(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_IGAIN0); }

    /**
     * Receive Proportional Gain 1
     * @param id ID
     * @return GAin
     */
    uint32_t getKp1(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_PGAIN1); }

    /**
     * Receive Derivative Gain 1
     * @param id ID
     * @return GAin
     */
    uint32_t getKd1(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_DGAIN1); }

    /**
     * Receive Integral Gain 1
     * @param id ID
     * @return Gain
     */
    uint32_t getKi1(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_IGAIN1); }

    /**
     * Receive Proportional Gain 2
     * @param id ID
     * @return GAin
     */
    uint32_t getKp2(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_PGAIN2); }

    /**
     * Receive Derivative Gain 2
     * @param id ID
     * @return GAin
     */
    uint32_t getKd2(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_DGAIN2); }

    /**
     * Receive Integral Gain 2
     * @param id ID
     * @return Gain
     */
    uint32_t getKi2(const ID_t id) { return readLong<uint32_t>(id, ADDRESS_IGAIN2); }

    /**
     * Get MCU Temperature
     * @param id ID
     * @return Temperature [1/100 degree Celsius]
     */
    int16_t getMCUTemperature(const ID_t id) { return readShort<int16_t>(id, ADDRESS_MCU_TEMPERATURE); }

    /**
     * Get Motor Temperature
     * @param id ID
     * @return Temperature [1/100 degree Celsius]
     */
    int16_t getMotorTemperature(const ID_t id) { return readShort<int16_t>(id, ADDRESS_MOTOR_TEMPERATURE); }

    /**
     * Get Motor Current
     * @param ID id
     * @return Electric Current [mA]
     */
    int16_t getActualCurrent(const ID_t id) { return readShort<int16_t>(id, ADDRESS_MOTOR_CURRENT); }

    /**
     * Set Target Current 
     * @param id ID
     * @param current Electric Current
     */
    void setTargetCurrent(const ID_t id, const int16_t current) {
      writeShort<int16_t>(id, ADDRESS_TARGET_CURRENT, current);
    }
    /**
     * Set Target Velocity to ID
     * @param id ID
     * @param vel Velocity [deg/100sec]
     */
    void setTargetVelocity(const ID_t id, const int16_t vel) {writeShort<int16_t>(id, ADDRESS_TARGET_VELOCITY, vel);}

    void setTargetPosition(const ID_t id, const int16_t pos) {writeShort<int16_t>(id, ADDRESS_TARGET_POSITION, pos);}

    int16_t getActualPosition(const ID_t id) { return readShort<int16_t>(id, ADDRESS_ACTUAL_POSITION); }
    /**
     * Get Current Actual Velocity
     * @param id ID
     * @return Velocity [deg/100sec]
     */
    int16_t getActualVelocity(const ID_t id) { return readShort<int16_t>(id, ADDRESS_TARGET_VELOCITY); }

    /**
     * Reset Motor
     * @param id ID
     */
    void resetMotor(const ID_t id) { reset(id); }

    /**
     * Get Encoder Count
     * @param id ID
     * @return Encoder Count 12bit per rotation.
     */
    uint16_t getEncoderCount(const ID_t id) { return readShort<uint16_t>(id, ADDRESS_ENCODER_COUNT); }


    /**
     * Get Total Encoder Count
     * @param id ID
     * @return Encoder Count 12bit per rotation, this buffer is 32bit counter (signed)
     */
    int32_t getEncoderTotalCount(const ID_t id) { return readLong<int16_t>(id, ADDRESS_ENCODER_TOTAL_COUNT); }
  };

};
