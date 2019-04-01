
#include "b3m.h"
using namespace kondo;

B3M::B3M(const std::string& filename, const int32_t baudrate) {
  m_pSerialPort = new ssr::SerialPort(filename.c_str(), baudrate);
}


B3M::~B3M() {
  delete m_pSerialPort;
}


void B3M::sendPacket(const Packet& packet) {
  packet.serialize(m_pPacketBuffer);
  m_pSerialPort->Write(m_pPacketBuffer, packet.size());
}


void B3M::receivePacket(Packet* packet) {
  uint8_t c;
  while(m_pSerialPort->GetSizeInRxBuffer() <= 0) {
    ssr::Thread::Sleep(PACKET_WAIT_SLEEP_TIME);
  }
  
  m_pSerialPort->Read(&c, 1);
  m_pPacketBuffer[0] = c;

  while(m_pSerialPort->GetSizeInRxBuffer() < c-1) {
    ssr::Thread::Sleep(PACKET_WAIT_SLEEP_TIME);
  }

  m_pSerialPort->Read(m_pPacketBuffer + 1, c-1);
  try {
    packet->deserialize(m_pPacketBuffer);
  } catch (ChecksumException &ex) {
    ex.id = packet->id;
    throw;
  }
}

void B3M::checkError(const ID_t id, const option_t option, const status_t status) {
  if (status > 0) {
    switch(option) {
    case OPTION_ERROR_STATUS:
      throw ErrorStatusException(id, status);
    case OPTION_SYSTEM_STATUS:
      throw SystemException(id, status);
    case OPTION_MOTOR_STATUS:
      throw MotorException(id, status);
    case OPTION_COMMAND_STATUS:
      throw CommandException(id, status);
    case OPTION_UART_STATUS:
      throw UARTException(id, status);
    default:
      throw B3MException(id, 0);
    }
  }
}

void B3M::load(const ID_t id) {
  ssr::MutexBinder binder(m_PacketMutex);
  m_Packet.command = COMMAND_LOAD;
  m_Packet.option  = OPTION_ERROR_STATUS;
  m_Packet.id = id;
  m_Packet.data_length = 0;
  sendPacket(m_Packet);
  receivePacket(&m_Packet);
  checkError(id, OPTION_ERROR_STATUS, m_Packet.status());
}

void B3M::save(const ID_t id) {
  ssr::MutexBinder binder(m_PacketMutex);
  m_Packet.command = COMMAND_SAVE;
  m_Packet.option  = OPTION_ERROR_STATUS;
  m_Packet.id = id;
  m_Packet.data_length = 0;
  sendPacket(m_Packet);
  receivePacket(&m_Packet);
  checkError(id, OPTION_ERROR_STATUS, m_Packet.status());
}

void B3M::reset(const ID_t id) {
  ssr::MutexBinder binder(m_PacketMutex);
  m_Packet.command = COMMAND_RESET;
  m_Packet.option  = OPTION_ERROR_STATUS;
  m_Packet.id = id;
  m_Packet.data_length = 0;
  sendPacket(m_Packet);
  //receivePacket(&m_Packet);
  //checkError(OPTION_ERROR_STATUS, m_Packet.status());
}

void B3M::read(const ID_t id, const address_t address, const uint8_t length, uint8_t *buffer)
{
  ssr::MutexBinder binder(m_PacketMutex);
  m_Packet.command = COMMAND_READ;
  m_Packet.option  = OPTION_ERROR_STATUS;
  m_Packet.id = id;
  m_Packet.data_length = 2;
  m_Packet.data[0] = address;
  m_Packet.data[1] = length;
  sendPacket(m_Packet);
  receivePacket(&m_Packet);
  checkError(id, OPTION_ERROR_STATUS, m_Packet.status());
  memcpy(buffer, m_Packet.data, length);
}

void B3M::write(const ID_t id, const address_t address, const uint8_t length, const uint8_t *buffer)
{
  ssr::MutexBinder binder(m_PacketMutex);
  m_Packet.command = COMMAND_WRITE;
  m_Packet.option  = OPTION_ERROR_STATUS;
  m_Packet.id = id;
  m_Packet.data_length = length + 2;
  memcpy(m_Packet.data, buffer, length);
  m_Packet.data[length  ] = address;
  m_Packet.data[length+1] = 1;
  sendPacket(m_Packet);
  receivePacket(&m_Packet);
  checkError(id, OPTION_ERROR_STATUS, m_Packet.status());
}

void B3M::position(const ID_t id, const int16_t pos, const uint16_t time)
{
  ssr::MutexBinder binder(m_PacketMutex);
  m_Packet.command = COMMAND_POSITION;
  m_Packet.option  = OPTION_ERROR_STATUS;
  m_Packet.id = id;
  m_Packet.data_length = 4;
  serialize_short<int16_t>(m_Packet.data+0, pos);
  serialize_short<uint16_t>(m_Packet.data+2, time);
  sendPacket(m_Packet);
  receivePacket(&m_Packet);
  checkError(id, OPTION_ERROR_STATUS, m_Packet.status());
}

