#pragma once

#include <sstream>
#include <string>
#include <exception>

#include "b3mcommon.h"

namespace kondo {
  class B3MException : public std::exception {
  public:
    ID_t id;
    std::string message;
    uint8_t errorCode;
  public:
    B3MException(ID_t id, uint8_t errorCode) { this->id = id; this->errorCode = errorCode;}
    virtual ~B3MException() throw() {}

  public:
    const char *what() const throw() {
      if (errorCode == 0) {
	return message.c_str();
      }
      std::ostringstream ss;
      ss << message << " (id=" << id << ", errorCode=" << errorCode << ")";
      return ss.str().c_str();
    }
  };

  class TimeoutException : public B3MException {
  public:
  TimeoutException(ID_t id) : B3MException(id, 0) {
      message = "TimeoutException";
    }
  };

  class ChecksumException : public B3MException {

  public:
  ChecksumException(ID_t id, ID_t receivedID) : B3MException(id, 0) {
      std::ostringstream ss;
      ss << "ChecksumException(received_ID=" << receivedID << " <= this may be invalid)";
      message = ss.str();
    }
  };

  class ErrorStatusException : public B3MException {
  public:
  ErrorStatusException(ID_t id, status_t status = 0) : B3MException(id, status) {
      message = "ErrorStatusException";
    }
  };

  class SystemException : public B3MException {
  public:
  SystemException(ID_t id, status_t status = 0) : B3MException(id, status) {
      message = "SystemException";
    }
  };

  class MotorException : public B3MException {
  public:
  MotorException(ID_t id, status_t status = 0) : B3MException(id, status) {
      message = "MotorException";
    }
  };

  class UARTException : public B3MException {
  public:
  UARTException(ID_t id, status_t status = 0) : B3MException(id, status) {
      message = "UARTException";
    }
  };

  class CommandException : public B3MException {
  public:
  CommandException(ID_t id, status_t status = 0) : B3MException(id, status) {
      message = "CommandException";
    }
  };

};

