#include <iostream>


#include "b3m.h"
#include "Console.h"

using namespace kondo;

#define BAUDRATE 1500000

B3M* pb3m;

int main(int argc, char* argv[]) {
  try {
    ssr::init_scr();

  std::cout << "---- B3M Test Program ----" << std::endl;
  if (argc <= 1) {
    std::cout << "Invalid Usage." << std::endl;
    std::cout << std::endl;
    std::cout << "Usgae:  $ demo [DEVICE_FILE]" << std::endl;
    std::cout << std::endl;
    return -1;
  }

  const ID_t id = 0;
  pb3m = new B3M(argv[1], BAUDRATE);

  pb3m->setMode(id, OPERATION_MODE_FREE);
  pb3m->setGainPresetNumber(id, 1);
  pb3m->setMode(id, OPERATION_MODE_NORMAL | CONTROL_MODE_VELOCITY);
  pb3m->setTargetVelocity(id, 10000); // 10 deg/sec * 100

  for (int i = 0;i < 60;i++) {
    ssr::clear_scr();
  std::cout << "------------------------------------" << std::endl;
  std::cout << "- COUNT : " << i+1 << "/60" << std::endl;
  std::cout << "- ID  : " << id << std::endl;
  std::cout << "- KP0 : " << pb3m->getKp0(id) << std::endl;
  std::cout << "- KI0 : " << pb3m->getKi0(id) << std::endl;
  std::cout << "- KD0 : " << pb3m->getKd0(id) << std::endl;
  std::cout << "- KP1 : " << pb3m->getKp1(id) << std::endl;
  std::cout << "- KI1 : " << pb3m->getKi1(id) << std::endl;
  std::cout << "- KD1 : " << pb3m->getKd1(id) << std::endl;
  std::cout << "- KP2 : " << pb3m->getKp2(id) << std::endl;
  std::cout << "- KI2 : " << pb3m->getKi2(id) << std::endl;
  std::cout << "- KD2 : " << pb3m->getKd2(id) << std::endl;
  std::cout << "- MCU   TEMPERATURE : " << pb3m->getMCUTemperature(id) / 100.0 << std::endl;
  std::cout << "- MOTOR TEMPERATURE : " << pb3m->getMotorTemperature(id) / 100.0 << std::endl;
  std::cout << "- ENCODER TOTAL     : " << pb3m->getEncoderTotalCount(id) << std::endl;
  std::cout << "------------------------------------" << std::endl;

  ssr::Thread::Sleep(500);  
  }

  ssr::exit_scr();
  pb3m->setTargetVelocity(id, 0);
  pb3m->setMode(id, OPERATION_MODE_FREE);

  std::cout << "---- B3M Test Program End----" << std::endl;
  } catch (std::exception& e) {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  return 0;
}